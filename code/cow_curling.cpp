#include <iostream>
#include <complex>
#include <stack>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

int sqr_dis(complex<float> p1, complex<float> p2) {
    return (p1.real() - p2.real()) * (p1.real() - p2.real()) + (p1.imag() - p2.imag()) * (p1.imag() - p2.imag());
}

// 0 --> p, q and r are colinear
// 1 --> Clockwise
// -1 --> Counterclockwise
int orientation(complex<float> a, complex<float> b, complex<float> c) {
    double area = (b.real() - a.real()) * (c.imag() - a.imag()) - (b.imag() - a.imag()) * (c.real() - a.real());
    if (area > 0)
        return -1;
    else if (area < 0)
        return 1;
    return 0;
}

struct PolarCmp {
    complex<float> p0;
    PolarCmp(complex<float> p0) {
        this->p0 = p0;
    }

    bool operator()(complex<float> p1, complex<float> p2) { 
        int ori = orientation(this->p0, p1, p2); 

        if (ori == 0) {
            return (sqr_dis(this->p0, p1) < sqr_dis(this->p0, p2));
        }

        return (ori == -1);
    }
};

complex<float> next_to_top(stack<complex<float>> &hull) { 
    complex<float> p = hull.top();
    hull.pop();
    complex<float> result = hull.top();
    hull.push(p);
    return result;
}

bool point_cmp(complex<float> p1, complex<float> p2) {
    if (p1.imag() < p2.imag()) {
        return true;
    }
    if (p1.imag() == p2.imag()) {
        return (p1.real() < p2.real());
    }
    return false;
}

vector<complex<float>> convex_hull(vector<complex<float>> points) {
    int n = points.size();
    complex<float> p0 = points[0];
    sort(points.begin() + 1, points.end(), PolarCmp(p0));

    int m = 1;
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0) {
            i++; 
        }
        points[m] = points[i];
        m++;
    }

    stack<complex<float>> hull;
    hull.push(points[0]);
    hull.push(points[1]);
    hull.push(points[2]);

    for (int i = 3; i < m; i++) {
        while (orientation(next_to_top(hull), hull.top(), points[i]) != -1) {
          hull.pop();
        }
        hull.push(points[i]);
    }

    vector<complex<float>> hull_vec;
    while (!hull.empty()) {
        hull_vec.push_back(hull.top());
        hull.pop();
    }
    reverse(hull_vec.begin(), hull_vec.end());

    return hull_vec;
}

int count_in_convec_hull(vector<complex<float>>& hull, vector<complex<float>> points) {
    int n = hull.size();

    int r_edge = 0, l_edge = 0;
    int count = 0;

    for (auto p : points) {
        while (r_edge + 1 < n && p.imag() > hull[r_edge + 1].imag()) {
            r_edge++;
        }

        while (l_edge - 1 + n >= 0 && p.imag() > hull[l_edge - 1 + n].imag()) {
            l_edge--;
        }

        if (r_edge + 1 >= n || l_edge - 1 + n < 0) {
            break;
        }

        if ((orientation(p, hull[r_edge], hull[r_edge + 1]) * 
             orientation(p, hull[(l_edge + n) % n], hull[l_edge - 1 + n]) <= 0) && 
            p.imag() >= hull[r_edge].imag()) {
            count++;
        }
    }

    return count;
}

int main() {
    int n;
    ifstream fin("data/cow_curling/cow_curling_data.txt", ifstream::in);
    fin >> n;

    vector<complex<float>> red_points;
    for (int i = 0; i < n; i++) {
        int x, y;
        fin >> x >> y;

        red_points.emplace_back(x, y);
    }

    vector<complex<float>> blue_points;
    for (int i = 0; i < n; i++) {
        int x, y;
        fin >> x >> y;

        blue_points.emplace_back(x, y);
    }
    sort(red_points.begin(), red_points.end(), point_cmp);
    sort(blue_points.begin(), blue_points.end(), point_cmp);

    auto red_hull = convex_hull(red_points);
    int red_score = count_in_convec_hull(red_hull, blue_points);

    auto blue_hull = convex_hull(blue_points);
    int blue_score = count_in_convec_hull(blue_hull, red_points);

    cout << red_score << " " << blue_score << endl;
}
#include <iostream>
#include <complex>
#include <stack>
#include <algorithm>
#include <vector>

using namespace std;

complex<float> p0;

complex<float> next_to_top(stack<complex<float>> &hull) { 
    complex<float> p = hull.top();
    hull.pop();
    complex<float> result = hull.top();
    hull.push(p);
    return result;
}

void swap(complex<float>& p1, complex<float> p2) {
    complex<float> temp;
    temp = p1;
    p1 = p2;
    p2 = temp;
}

int sqr_dis(complex<float> p1, complex<float> p2) {
    return (p1.real() - p2.real()) * (p1.real() - p2.real()) + (p1.imag() - p2.imag()) * (p1.imag() - p2.imag());
}

// 0 --> p, q and r are colinear
// 1 --> Clockwise
// -1 --> Counterclockwise
int orientation(complex<float> a, complex<float> b, complex<float> c) {
    int area = (b.real() - a.real()) * (c.imag() - a.imag()) - (b.imag() - a.imag()) * (c.real() - a.real());
    if (area > 0)
        return -1;
    else if (area < 0)
        return 1;
    return 0;
}

bool polar_cmp(complex<float> p1, complex<float> p2) { 
    int ori = orientation(p0, p1, p2); 

    if (ori == 0) {
        return (sqr_dis(p0, p1) < sqr_dis(p0, p2));
    }

    return (ori == -1);
}

void convex_hull(vector<complex<float>> points, int n) { 
    int ymin = points[0].imag(), min = 0;
    for (int i = 0; i < n; i++) {
      int y = points[i].imag();
      if (y < ymin || (y == ymin && points[i].real() < points[min].real())) {
        ymin = points[i].imag();
        min = i;
      }
    }

    swap(points[0], points[min]);
    p0 = points[0];
    sort(points.begin(), points.end(), polar_cmp);

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

    while(!hull.empty()) {
      cout << hull.top() << endl;
      hull.pop();
    }
}

int main() { 
    vector<complex<float>> points{{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    int n = 8;

    convex_hull(points, n);
}
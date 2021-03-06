#include <algorithm>
#include <complex>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int sqr_dis(complex<float> p1, complex<float> p2) {
  return (p1.real() - p2.real()) * (p1.real() - p2.real()) +
         (p1.imag() - p2.imag()) * (p1.imag() - p2.imag());
}

// 0 --> p, q and r are colinear
// 1 --> Clockwise
// -1 --> Counterclockwise
int orientation(complex<float> a, complex<float> b, complex<float> c) {
  int area =
      (b.real() - a.real()) * (c.imag() - a.imag()) - (b.imag() - a.imag()) * (c.real() - a.real());
  if (area > 0)
    return -1;
  else if (area < 0)
    return 1;
  return 0;
}

struct PolarCmp {
  complex<float> p0;
  PolarCmp(complex<float> p0) { this->p0 = p0; }

  bool operator()(complex<float> p1, complex<float> p2) {
    int ori = orientation(this->p0, p1, p2);

    if (ori == 0) {
      return (sqr_dis(this->p0, p1) < sqr_dis(this->p0, p2));
    }

    return (ori == -1);
  }
};

complex<float> next_to_top(stack<complex<float>>& hull) {
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

vector<complex<float>> convex_hull(vector<complex<float>>& points) {
  int n = points.size();
  int min_index = min_element(points.begin(), points.end(), point_cmp) - points.begin();

  swap(points[0], points[min_index]);
  complex<float> p0 = points[0];
  sort(points.begin(), points.end(), PolarCmp(p0));

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

int main() {
  vector<complex<float>> points{{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};

  auto hull = convex_hull(points);
  for (auto point : hull) {
    cout << point << endl;
  }
}
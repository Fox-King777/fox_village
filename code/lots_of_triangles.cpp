#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

using namespace std;

bool complex_cmp(complex<double> a, complex<double> b) {
  if (real(a) == real(b)) return imag(a) > imag(b);
  return real(a) < real(b);
}

float cross_prod(complex<float> p0, complex<float> p1) {
  return p0.real() * p1.imag() - p0.imag() * p1.real();
}

bool below(complex<float> a, complex<float> b, complex<float> t) {
  return (a.real() <= t.real() && b.real() > t.real() && cross_prod(b - a, a - t) > 0);
}

int count_below(complex<float> a, complex<float> b, vector<complex<float>>& trees) {
  int sum = 0;

  for (auto t : trees) {
    if (below(a, b, t)) {
      sum++;
    }
  }
  return sum;
}

int main() {
  int n;
  vector<complex<float>> trees;

  cin >> n;
  vector<int> counts(n, 0);

  for (int i = 0; i < n; ++i) {
    float x, y;
    cin >> x >> y;
    trees.emplace_back(x, y);
  }

  sort(trees.begin(), trees.end(), complex_cmp);

  vector<vector<int>> belows(n, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      belows[i][j] = count_below(trees[i], trees[j], trees);
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      for (int k = j + 1; k < n; ++k) {
        int blue = belows[i][j];
        int red = belows[j][k];
        int black = belows[i][k];
        int diff = blue + red - black;

        int num_trees = diff >= 0 ? diff : (-diff - 1);
        ++counts[num_trees];
      }
    }
  }

  for (int i = 0; i < n - 2; ++i) {
    cout << counts[i] << endl;
  }

  /*
  edges of triangle:
  green: left to mid
  red: mid to right
  blue: left to right
  */

  /*
  4 cases:
  1: blue is below green and red. /_\
    below green + below red - below blue = # trees in triangle
  2: blue is above grean and red. \-/
    below blue - below red - below green - 1
  3. green is vertical
    below red - below blue - 1
  4. red is vertical
    below green - blue
  */
}

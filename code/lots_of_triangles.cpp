#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <algorithm>

using namespace std;

bool complex_cmp(complex<double> a, complex<double> b)
{
    if (real(a) == real(b))
        return imag(a) < imag(b);
    return real(a) < real(b);
}

float cross_prod(complex<float> p0, complex<float> p1) {
  return p0.real() * p1.imag() - p0.imag() * p1.real();
}

bool below(complex<float> a, complex<float> b, complex<float> tree) {
  return (a.real() <= tree.real() && b.real() > tree.real() && cross_prod(a - tree, b - a) < 0);
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

  for (int i = 0; i < n; ++i) {
    float x, y;
    cin >> x >> y;
    trees.emplace_back(x, y);
  }


  for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; j++) {
        cout << trees[i] << " " << trees[j] << " " << count_below(trees[i], trees[j], trees) << endl;
      }
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
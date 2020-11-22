#include <complex>
#include <iostream>

using namespace std;

int main() {
  complex<float> p0(0.5, 0.5);
  complex<float> p1(0.5, 1.8);
  complex<float> p2(0.5, -0.8);
  auto v1 = p2 - p0;
  auto v2 = p1 - p0;

  cout << "v1=" << v1 << " v2=" << v2 << endl << " -v2=" << -v2;
}
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void solution() {
  int n;
  cin >> n;

  vector<long long> x(n);
  vector<long long> y(n);
  for (int i = 0; i < n; ++i) {
    cin >> x[i] >> y[i];
  }
  sort(x.begin(), x.end());
  sort(y.begin(), y.end());

  long long good_x = x[n / 2] - x[(n - 1) / 2] + 1;
  long long good_y = y[n / 2] - y[(n - 1) / 2] + 1;
  cout << good_x * good_y << endl;
}

int main() {
  int t;
  cin >> t;

  for (int i = 0; i < t; ++i) {
    solution();
  }
}
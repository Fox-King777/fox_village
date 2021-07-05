#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void solve() {
  int n;
  cin >> n;

  vector<long long> m;
  vector<long long> d;
  for (int i = 0; i < 2 * n; ++i) {
    int x, y;
    cin >> x >> y;
    if (x == 0) {
      m.push_back(abs(y));
    } else {
      d.push_back(abs(x));
    }
  }
  sort(m.begin(), m.end());
  sort(d.begin(), d.end());

  double ans = 0;
  for (int i = 0; i < n; ++i) {
    ans += sqrt(pow(m[i], 2) + pow(d[i], 2));
  }

  cout << setprecision(15) << ans << endl;
}

int main() {
  int t;
  cin >> t;

  for (int i = 0; i < t; ++i) {
    solve();
  }
}
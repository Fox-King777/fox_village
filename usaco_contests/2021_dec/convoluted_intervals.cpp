#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> intv(n);
  vector<long long> s(m * 2 + 1, 0);
  vector<long long> e(m * 2 + 1, 0);
  for (int i = 0; i < n; ++i) {
    cin >> intv[i].first >> intv[i].second;
    s[intv[i].first]++;
    e[intv[i].second]++;
  }

  for (int k = 0; k <= 2 * m; ++k) {
    long long count = 0;
    long long ki_cnt = 0;
    long long kj_cnt = 0;

    for (int i = m; i > k; --i) {
      kj_cnt += e[i];
      if (i < m) {
        kj_cnt -= s[i + 1];
      }
    }

    for (int ki = 0; ki <= k; ++ki) {
      int kj = k - ki;

      long long a = s[ki];
      ki_cnt += a;
      if (ki > 0) {
        ki_cnt -= e[ki - 1];
      }

      long long b = e[kj];
      kj_cnt += b;
      if (kj < m) {
        kj_cnt -= s[kj + 1];
      }
      count += a * kj_cnt + b * ki_cnt - a * b;
    }
    cout << count << endl;
  }
}

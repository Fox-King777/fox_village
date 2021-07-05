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

bool cmp(long long a, long long b) { return a > b; }

void solve() {
  long long n, m, a, b;
  cin >> n >> m >> a >> b;

  vector<long long> c(m);
  for (int i = 0; i < m; ++i) {
    cin >> c[i];
  }

  sort(c.begin(), c.end(), cmp);

  int tot = a - 1;
  if (a > b) {
    tot = n - a;
  }

  int boom = abs(b - a) - 1;
  tot += boom;

  int cnt = 0;
  for (int i = 0; i < m; ++i) {
    if (cnt == boom) {
      break;
    }

    if (c[i] <= tot) {
      cnt++;
      tot--;
    }
  }
  cout << cnt << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
}
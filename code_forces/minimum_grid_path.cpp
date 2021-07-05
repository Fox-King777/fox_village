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

void solve() {
  int n;
  cin >> n;

  long long presums = 0;
  long long minx = numeric_limits<long long>::max(), miny = numeric_limits<long long>::max();
  long long ans = numeric_limits<long long>::max();
  int xid = 0, yid = 0;
  for (int i = 0; i < n; ++i) {
    long long num;
    cin >> num;

    presums += num;

    if (i % 2 == 0) {
      minx = min(minx, num);
      xid++;
    } else {
      miny = min(miny, num);
      yid++;
    }

    if (yid > 0) {
      ans = min(ans, presums + (n - xid) * minx + (n - yid) * miny);
    }
  }

  cout << ans << endl;
}

int main() {
  int t;
  cin >> t;

  for (int i = 0; i < t; ++i) {
    solve();
  }
}
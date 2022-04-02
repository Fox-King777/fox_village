#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    long long s, t;
    cin >> s >> t;

    int ans1 = 0;
    while (s > t) {
      if (s % 2 == 0) {
        s /= 2;
      } else {
        s++;
        s /= 2;
        ans1++;
      }
      ans1++;
    }

    if (s == t) {
      cout << ans1 << endl;
      continue;
    }

    vector<pair<long long, int>> destruct;  // f = val, s = weight
    int w = 0;
    while (s != 1) {
      destruct.push_back(make_pair(s, w));
      if (s % 2 == 1) {
        s++;
        w++;
      }
      s /= 2;
      w++;
    }
    destruct.push_back(make_pair(1, w + 1));

    int ans2 = numeric_limits<int>::max();
    for (int j = 0; j < destruct.size(); ++j) {
      long long d = destruct[j].first;
      int count = 0;
      while (d <= t) {
        d *= 2;
        count++;
      }
      d /= 2;
      count--;
      int left_over = t - d;

      int num_add = 0;
      for (int p = count; p >= 0; --p) {
        num_add += left_over / pow(2, p);
        left_over -= (int)(left_over / pow(2, p)) * pow(2, p);
      }
      ans2 = min(ans2, count + destruct[j].second + num_add);
    }

    cout << ans1 + ans2 << endl;
  }
}
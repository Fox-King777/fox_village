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

struct patch {
  long long x, t;
};

bool patch_cmp(patch a, patch b) { return a.x < b.x; }

int main() {
  int k, m, n;
  cin >> k >> m >> n;

  vector<patch> patches(k);
  for (int i = 0; i < k; ++i) {
    cin >> patches[i].x >> patches[i].t;
  }
  sort(patches.begin(), patches.end(), patch_cmp);

  vector<long long> c(m);
  for (int i = 0; i < m; ++i) {
    cin >> c[i];
  }
  c.push_back(1000000000000);
  sort(c.begin(), c.end());

  int p1 = 0, p2 = 0;
  vector<long long> gains;
  for (int i = 0; i < c.size(); ++i) {
    long long l;
    if (i == 0) {
      l = 1000000000;
    } else {
      l = c[i] - c[i - 1];
    }

    long long tot_sum = 0;
    long long cur_sum = 0;
    long long one_max = 0;
    p1 = p2;
    while (p2 < k && patches[p2].x < c[i]) {
      tot_sum += patches[p2].t;
      cur_sum += patches[p2].t;

      while (patches[p2].x - patches[p1].x >= l / 2) {
        cur_sum -= patches[p1].t;
        p1++;
      }
      one_max = max(one_max, cur_sum);

      p2++;
    }

    gains.push_back(one_max);
    gains.push_back(tot_sum - one_max);
  }
  sort(gains.begin(), gains.end(), greater<long long>());

  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    ans += gains[i];
  }

  cout << ans;
}
/*
6 5 2
0 4
4 6
8 10
10 8
12 12
13 14
2
3
5
7
11
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Interval {
  long long s, e;
};

bool intv_cmp(Interval a, Interval b) { return a.s < b.s; }

bool if_works(vector<Interval>& grass, long long d, int n) {
  long long pos = grass[0].s;

  int count = 0;
  for (auto& i : grass) {
    while (max(pos + d, i.s) <= i.e) {
      pos = max(pos + d, i.s);
      count++;
      if (count >= n) {
        break;
      }
    }
    if (count >= n) {
      break;
    }
  }

  return count >= n;
}

int main() {
  ifstream fin("testdata/social_distancing/10.in", ifstream::in);

  int n, m;
  fin >> n >> m;

  vector<Interval> grass(m);
  for (int i = 0; i < m; ++i) {
    fin >> grass[i].s >> grass[i].e;
  }
  sort(grass.begin(), grass.end(), intv_cmp);

  long long hi = grass[m - 1].e - grass[0].s, lo = 0;
  long long ans = 0;
  while (hi >= lo) {
    long long mid = (hi + lo) / 2;
    if (!if_works(grass, mid, n)) {
      hi = mid - 1;
    } else {
      ans = max(ans, mid);
      lo = mid + 1;
    }
  }

  cout << ans;
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=1038
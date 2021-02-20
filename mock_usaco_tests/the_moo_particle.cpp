#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>

using namespace std;

void floodfill(vector<pair<long long, long long>>& xy, vector<bool>& mark, int idx) {
  queue<int> q;
  q.push(idx);
  mark[idx] = true;

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (int i = 0; i < xy.size(); ++i) {
      if (!mark[i] && ((xy[i].first >= xy[v].first && xy[i].second >= xy[v].second) ||
                       (xy[i].first <= xy[v].first && xy[i].second <= xy[v].second))) {
        mark[i] = true;
        q.push(i);
      }
    }
  }
}

int main() {
  ifstream fin("testdata/the_moo_particle/1.in", ifstream::in);

  int n;
  fin >> n;

  vector<pair<long long, long long>> xy(n);
  for (int i = 0; i < n; ++i) {
    fin >> xy[i].first >> xy[i].second;
  }

  vector<bool> mark(n, false);
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (!mark[i]) {
      ans++;
      floodfill(xy, mark, i);
    }
  }

  cout << ans;
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=1040
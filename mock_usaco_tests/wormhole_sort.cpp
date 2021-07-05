#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

void floodfill(vector<vector<pair<int, long long>>>& adjlist, vector<int>& mark, long long minw,
               int id, int c) {
  queue<int> q;
  q.push(id);
  mark[id] = c;
  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (auto& e : adjlist[v]) {
      if (e.second >= minw && mark[e.first] == -1) {
        mark[e.first] = c;
        q.push(e.first);
      }
    }
  }
}

bool ok(vector<int>& cows, vector<vector<pair<int, long long>>>& adjlist, long long minw) {
  vector<int> mark(cows.size(), -1);
  int c = 0;
  for (int i = 0; i < mark.size(); ++i) {
    if (mark[i] == -1) {
      floodfill(adjlist, mark, minw, i, c);
      c++;
    }
  }

  for (int i = 0; i < cows.size(); ++i) {
    if (mark[i] != mark[cows[i]]) {
      return false;
    }
  }
  return true;
}

int main() {
  ifstream fin("testdata/wormhole_sort/10.in", ifstream::in);

  int n, m;
  fin >> n >> m;

  vector<int> cows(n);
  vector<vector<pair<int, long long>>> adjlist(n);
  for (int i = 0; i < n; ++i) {
    fin >> cows[i];
    cows[i]--;
  }
  for (int i = 0; i < m; ++i) {
    int a, b;
    long long w;
    fin >> a >> b >> w;
    a--;
    b--;
    adjlist[a].push_back(make_pair(b, w));
    adjlist[b].push_back(make_pair(a, w));
  }

  int sol = -1;
  int lo = 1, hi = 1000000001;
  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;

    if (ok(cows, adjlist, mid)) {
      sol = max(sol, mid);
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }

  cout << sol;
}
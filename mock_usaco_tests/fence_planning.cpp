#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

struct Point {
  long long x, y;
};

long long per(long long maxx, long long minx, long long maxy, long long miny) {
  return (maxx - minx) * 2 + (maxy - miny) * 2;
}

long long solve(vector<vector<int>>& adjlist, vector<bool>& mark, vector<Point>& cows, int idx) {
  queue<int> q;
  q.push(idx);
  mark[idx] = true;
  vector<Point> network;
  network.push_back(cows[idx]);

  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int i = 0; i < adjlist[v].size(); ++i) {
      if (!mark[adjlist[v][i]]) {
        q.push(adjlist[v][i]);
        network.push_back(cows[adjlist[v][i]]);
        mark[adjlist[v][i]] = true;
      }
    }
  }

  long long maxx = numeric_limits<long long>::min(), minx = numeric_limits<long long>::max(),
            maxy = numeric_limits<long long>::min(), miny = numeric_limits<long long>::max();
  for (Point p : network) {
    maxx = max(maxx, p.x);
    minx = min(minx, p.x);
    maxy = max(maxy, p.y);
    miny = min(miny, p.y);
  }

  return per(maxx, minx, maxy, miny);
}

int main() {
  ifstream fin("testdata/fence_planning/10.in", ifstream::in);

  int n, m;
  fin >> n >> m;

  vector<Point> cows(n);
  for (int i = 0; i < n; ++i) {
    fin >> cows[i].x >> cows[i].y;
  }

  vector<vector<int>> adjlist(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    fin >> a >> b;
    a--;
    b--;
    adjlist[a].push_back(b);
    adjlist[b].push_back(a);
  }

  long long ans = numeric_limits<long long>::max();
  vector<bool> mark(n, false);
  for (int i = 0; i < n; ++i) {
    if (!mark[i]) {
      ans = min(ans, solve(adjlist, mark, cows, i));
    }
  }
  cout << ans;
}
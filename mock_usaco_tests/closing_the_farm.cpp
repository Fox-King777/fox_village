#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>

using namespace std;

bool fully_connected(vector<vector<int>>& adjlist, vector<int>& closed, int n, int init) {
  vector<bool> mark(n, false);
  queue<int> q;
  q.push(init);
  mark[init] = true;
  for (int i = 0; i < closed.size(); ++i) {
    mark[closed[i]] = true;
  }

  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int i = 0; i < adjlist[v].size(); ++i) {
      if (!mark[adjlist[v][i]]) {
        q.push(adjlist[v][i]);
        mark[adjlist[v][i]] = true;
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    if (!mark[i]) {
      return false;
    }
  }

  return true;
}

int main() {
  ifstream fin("testdata/closing_the_farm/10.in", ifstream::in);

  int n, m;
  fin >> n >> m;

  vector<vector<int>> adjlist(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    fin >> a >> b;
    a--;
    b--;
    adjlist[a].push_back(b);
    adjlist[b].push_back(a);
  }

  vector<int> closed_order(n);
  vector<int> closed;
  for (int i = 0; i < n; ++i) {
    fin >> closed_order[i];
    closed_order[i]--;
  }

  for (int i = 0; i < n; ++i) {
    if (fully_connected(adjlist, closed, n, closed_order[closed_order.size() - 1])) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
    closed.push_back(closed_order[i]);
  }
}
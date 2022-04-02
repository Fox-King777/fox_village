#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

bool floodfill(vector<vector<char>>& grid, pair<int, int> spoint) {
  vector<pair<int, int>> dir = {make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1),
                                make_pair(0, -1)};
  queue<pair<int, int>> q;
  vector<vector<bool>> mark(grid.size(), vector<bool>(grid[0].size(), false));
  q.push(spoint);
  mark[spoint.first][spoint.second] = true;

  while (!q.empty()) {
    pair<int, int> v = q.front();
    q.pop();

    if (v.first == grid.size() - 1 && v.second == grid[0].size() - 1) {
      return true;
    }

    for (pair<int, int> d : dir) {
      pair<int, int> npoint = make_pair(v.first + d.first, v.second + d.second);
      if (npoint.first < grid.size() && npoint.first >= 0 && npoint.second < grid[0].size() &&
          npoint.second >= 0 && !mark[npoint.first][npoint.second] &&
          grid[npoint.first][npoint.second] != '#') {
        mark[npoint.first][npoint.second] = true;
        q.push(npoint);
      }
    }
  }
  return false;
}

void solve() {
  int n, m;
  cin >> n >> m;

  vector<vector<char>> grid(n, vector<char>(m));
  vector<pair<int, int>> g;
  vector<pair<int, int>> b;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> grid[i][j];
      if (grid[i][j] == 'G') {
        g.push_back(make_pair(i, j));
      } else if (grid[i][j] == 'B') {
        b.push_back(make_pair(i, j));
      }
    }
  }

  vector<int> dirr = {1, -1, 0, 0};
  vector<int> dirc = {0, 0, 1, -1};
  for (auto e : b) {
    for (int i = 0; i < 4; ++i) {
      pair<int, int> around = make_pair(e.first + dirr[i], e.second + dirc[i]);
      if (around.first >= 0 && around.first < n && around.second >= 0 && around.second < m) {
        if (grid[around.first][around.second] == 'G') {
          cout << "NO" << endl;
          return;
        }
        if (grid[around.first][around.second] == '.') {
          grid[around.first][around.second] = '#';
        }
      }
    }
  }

  for (auto s : g) {
    if (!floodfill(grid, s)) {
      cout << "NO" << endl;
      return;
    }
  }
  cout << "YES" << endl;
}

int main() {
  int t;
  cin >> t;

  for (int i = 0; i < t; ++i) {
    solve();
  }
}
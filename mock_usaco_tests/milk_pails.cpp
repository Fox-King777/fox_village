#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void add(int x, int y, pair<int, int> cur, vector<vector<bool>>& mark, set<pair<int, int>>& q) {
  if (!mark[x][cur.second]) {
    mark[x][cur.second] = true;
    q.insert(make_pair(x, cur.second));
  }
  if (!mark[cur.first][y]) {
    mark[cur.first][y] = true;
    q.insert(make_pair(cur.first, y));
  }
  if (!mark[0][cur.second]) {
    mark[0][cur.second] = true;
    q.insert(make_pair(0, cur.second));
  }
  if (!mark[cur.first][0]) {
    mark[cur.first][0] = true;
    q.insert(make_pair(cur.first, 0));
  }

  int xl = cur.first + cur.second > y ? cur.first + cur.second - y : 0;
  int yl = cur.first + cur.second > x ? cur.first + cur.second - x : 0;
  if (!mark[xl][min(y, cur.first + cur.second)]) {
    mark[xl][min(y, cur.first + cur.second)] = true;
    q.insert(make_pair(xl, min(y, cur.first + cur.second)));
  }
  if (!mark[min(x, cur.first + cur.second)][yl]) {
    mark[min(x, cur.first + cur.second)][yl] = true;
    q.insert(make_pair(min(x, cur.first + cur.second), yl));
  }
}

int main() {
  ifstream fin("testdata/milk_pails/10.in", ifstream::in);

  int x, y, k, m;
  fin >> x >> y >> k >> m;

  vector<vector<bool>> mark(x + 1, vector<bool>(y + 1, false));
  set<pair<int, int>> q;
  mark[0][0] = true;
  q.insert(make_pair(0, 0));
  for (int i = 0; i < k; ++i) {
    set<pair<int, int>> neighbors;
    for (set<pair<int, int>>::iterator it = q.begin(); it != q.end(); ++it) {
      add(x, y, *it, mark, neighbors);
    }
    q = neighbors;
  }

  int ans = numeric_limits<int>::max();
  for (int i = 0; i < x + 1; ++i) {
    for (int j = 0; j < y + 1; ++j) {
      if (mark[i][j]) {
        ans = min(ans, abs(i + j - m));
      }
    }
  }

  cout << ans;
}
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

bool two_colors(vector<vector<char>>& grid, int st_r, int st_c, int l, int w) {
  unordered_set<char> colors;
  for (int i = st_r; i < st_r + l; ++i) {
    for (int j = st_c; j < st_c + w; ++j) {
      colors.insert(grid[i][j]);
    }
  }
  return colors.size() == 2;
}

void bfs_floodfill(vector<vector<char>>& grid, vector<vector<bool>>& mark2, int st_r, int st_c,
                   int init_r, int init_c, int l, int w, char color) {
  vector<int> dirr = {1, -1, 0, 0};
  vector<int> dirc = {0, 0, 1, -1};

  queue<pair<int, int>> q;
  q.push(make_pair(init_r, init_c));
  mark2[init_r][init_c] = true;

  while (!q.empty()) {
    pair<int, int> v = q.front();
    q.pop();

    for (int i = 0; i < 4; ++i) {
      if (v.first + dirr[i] < st_r + l && v.first + dirr[i] >= st_r &&
          v.second + dirc[i] < st_c + w && v.second + dirc[i] >= st_c) {
        if (!mark2[v.first + dirr[i]][v.second + dirc[i]] &&
            grid[v.first + dirr[i]][v.second + dirc[i]] == color) {
          mark2[v.first + dirr[i]][v.second + dirc[i]] = true;
          q.push(make_pair(v.first + dirr[i], v.second + dirc[i]));
        }
      }
    }
  }
}

bool is_plc(vector<vector<char>>& grid, int st_r, int st_c, int l, int w) {
  char c1 = grid[st_r][st_c];
  int c1_cnt = 0;
  int c2_cnt = 0;

  vector<vector<bool>> mark2(grid.size(), vector<bool>(grid.size(), false));
  for (int i = st_r; i < st_r + l; ++i) {
    for (int j = st_c; j < st_c + w; ++j) {
      if (!mark2[i][j]) {
        if (grid[i][j] == c1) {
          c1_cnt++;
          bfs_floodfill(grid, mark2, st_r, st_c, i, j, l, w, grid[i][j]);
        } else {
          c2_cnt++;
          bfs_floodfill(grid, mark2, st_r, st_c, i, j, l, w, grid[i][j]);
        }
      }
    }
  }

  return (min(c1_cnt, c2_cnt) == 1 && max(c1_cnt, c2_cnt) > 1);
}

void mark_area(vector<vector<set<int>>>& mark, int st_r, int st_c, int l, int w, int color_fill) {
  for (int i = st_r; i < st_r + l; ++i) {
    for (int j = st_c; j < st_c + w; ++j) {
      mark[i][j].insert(color_fill);
    }
  }
}

set<int> set_intersect(const set<int>& a, const set<int>& b) {
  set<int> intersection;
  for (auto x : a) {
    if (b.find(x) != b.end()) {
      intersection.insert(x);
    }
  }
  return intersection;
}

int main() {
  ifstream fin("testdata/wheres_bessie/3.in", ifstream::in);

  int n;
  fin >> n;

  vector<vector<char>> grid(n, vector<char>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      fin >> grid[i][j];
    }
  }

  vector<vector<set<int>>> mark(n, vector<set<int>>(n));
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int l = n - i; l > 0; --l) {
        for (int w = n - j; w > 0; --w) {
          if (set_intersect(mark[i][j], mark[i + l - 1][j + w - 1]).empty()) {
            if (two_colors(grid, i, j, l, w) && is_plc(grid, i, j, l, w)) {
              // cout << i << " " << j << " " << l << " " << w << endl;
              mark_area(mark, i, j, l, w, ans++);
            }
          }
        }
      }
    }
  }

  cout << ans << endl;
}
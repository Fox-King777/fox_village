#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

bool two_colors(vector<vector<char>>& grid, int st_r, int st_c, int l,
                int w) {  // check for exactly two colors
  vector<char> colors;
  colors.push_back('^');
  for (int i = st_r; i < st_r + l; ++i) {
    for (int j = st_c; j < st_c + w; ++j) {
      if (find(colors.begin(), colors.end(), grid[i][j]) == colors.end()) {
        colors.push_back(grid[i][j]);
      }
    }
  }

  if (colors.size() - 1 == 2) {
    /*cout << "does work" << endl;
    for (int i = st_r; i < st_r + l; i++) {
      for (int j = st_c; j < st_c + w; j++) {
        cout << grid[i][j] << " ";
      }
      cout << endl;
    }*/
    return true;
  }
  // cout << "doesn't work" << endl;
  return false;
}

void bfs_floodfill(vector<vector<char>>& grid, vector<vector<bool>>& mark2, int st_r, int st_c,
                   int init_r, int init_c, int l, int w, char color) {
  // cout << color << endl;
  vector<int> dirr = {1, -1, 0, 0};
  vector<int> dirc = {0, 0, 1, -1};

  queue<pair<int, int>> q;
  q.push(make_pair(init_r, init_c));
  mark2[init_r][init_c] = true;

  while (!q.empty()) {
    pair<int, int> v = q.front();
    q.pop();

    // cout << v.first << " " << v.second << endl;

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

bool is_plc(vector<vector<char>>& grid, vector<vector<bool>>& mark, int st_r, int st_c, int l,
            int w) {
  char c1 = grid[st_r][st_c];
  int c1_cnt = 0;
  int c2_cnt = 0;

  vector<vector<bool>> mark2(mark.size(), vector<bool>(mark.size(), false));
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

  // cout << endl << c1_cnt << " " << c2_cnt << endl;
  if (min(c1_cnt, c2_cnt) == 1 && max(c1_cnt, c2_cnt) > 1) {
    // cout << "is plc" << endl;
    for (int i = st_r; i < st_r + l; ++i) {
      for (int j = st_c; j < st_c + w; ++j) {
        mark[i][j] = true;
      }
    }
    return true;
  }
  // cout << "not plc" << endl;
  return false;
}

int main() {
  ifstream fin("testdata/where's_bessie/1.in", ifstream::in);

  int n;
  fin >> n;

  vector<vector<char>> grid(n, vector<char>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      fin >> grid[i][j];
    }
  }

  vector<vector<bool>> mark(n, vector<bool>(n, false));
  int ans = 0;
  for (int i = 0; i < n; ++i) {        // iterate through rows
    for (int j = 0; j < n; ++j) {      // iterate through columns
      for (int l = n; l > 0; --l) {    // all lengths possible
        for (int w = n; w > 0; --w) {  // all widths possible
          if (i + l <= n && j + w <= n &&
              (!mark[i][j] ||
               (mark[i][j] && !mark[i + l - 1][j + w - 1]))) {  // if rectangle in bounds
            // cout << i << " " << j << " " << l << " " << w << endl;
            if (two_colors(grid, i, j, l, w)) {  // if there are two colors in rectangle
              if (is_plc(grid, mark, i, j, l, w)) {
                ans++;
              }
            }
          }
        }
      }
    }
  }

  cout << ans;
}
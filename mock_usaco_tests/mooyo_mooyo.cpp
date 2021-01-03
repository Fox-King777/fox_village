#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void printGrid(vector<vector<char>>& grid) {
  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[i].size(); ++j) {
      cout << grid[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

bool check(vector<vector<char>>& grid, int k, int sr, int sc, char color) {
  vector<vector<bool>> mark(grid.size(), vector<bool>(10, false));
  vector<int> dirr = {1, -1, 0, 0};
  vector<int> dirc = {0, 0, 1, -1};

  queue<pair<int, int>> q;
  q.push(make_pair(sr, sc));
  mark[sr][sc] = true;
  int cnt = 0;
  while (!q.empty()) {
    pair<int, int> v = q.front();
    q.pop();
    cnt++;

    for (int i = 0; i < 4; ++i) {
      if (v.first + dirr[i] < grid.size() && v.first + dirr[i] >= 0 && v.second + dirc[i] < 10 &&
          v.second + dirc[i] >= 0 && !mark[v.first + dirr[i]][v.second + dirc[i]] &&
          grid[v.first + dirr[i]][v.second + dirc[i]] == color) {
        q.push(make_pair(v.first + dirr[i], v.second + dirc[i]));
        mark[v.first + dirr[i]][v.second + dirc[i]] = true;
      }
    }
  }
  return cnt >= k;
}

void floodfill(vector<vector<char>>& grid, vector<vector<bool>>& mark, int k, int sr, int sc,
               char color) {
  vector<int> dirr = {1, -1, 0, 0};
  vector<int> dirc = {0, 0, 1, -1};

  queue<pair<int, int>> q;
  q.push(make_pair(sr, sc));
  grid[sr][sc] = '0';
  mark[sr][sc] = true;
  while (!q.empty()) {
    pair<int, int> v = q.front();
    q.pop();

    for (int i = 0; i < 4; ++i) {
      if (v.first + dirr[i] < grid.size() && v.first + dirr[i] >= 0 && v.second + dirc[i] < 10 &&
          v.second + dirc[i] >= 0 && grid[v.first + dirr[i]][v.second + dirc[i]] != '0' &&
          grid[v.first + dirr[i]][v.second + dirc[i]] == color) {
        q.push(make_pair(v.first + dirr[i], v.second + dirc[i]));
        grid[v.first + dirr[i]][v.second + dirc[i]] = '0';
        mark[v.first + dirr[i]][v.second + dirc[i]] = true;
      }
    }
  }
}

bool col_gravity(vector<vector<char>>& grid, int c) {
  int bottom = grid.size() - 1;
  bool if_change = false;
  for (int i = grid.size() - 1; i >= 0; --i) {
    if (grid[i][c] != '0') {
      if (bottom != i) {
        if_change = true;
        grid[bottom][c] = grid[i][c];
        grid[i][c] = '0';
      }
      bottom--;
    }
  }

  return if_change;
}

bool gravity(vector<vector<char>>& grid, int C) {
  bool can_gravity = false;
  for (int c = 0; c < C; ++c) {
    can_gravity |= col_gravity(grid, c);
  }
  return can_gravity;
}

int main() {
  ifstream fin("testdata/mooyo_mooyo/9.in", ifstream::in);

  int n, k;
  fin >> n >> k;

  vector<vector<char>> grid(n, vector<char>(10));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 10; ++j) {
      fin >> grid[i][j];
    }
  }

  bool can_find = true;
  while (can_find) {
    vector<vector<bool>> mark(n, vector<bool>(10, false));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < 10; ++j) {
        if (!mark[i][j] && grid[i][j] != '0') {
          if (check(grid, k, i, j, grid[i][j])) {
            floodfill(grid, mark, k, i, j, grid[i][j]);
          }
        }
      }
    }

    can_find = gravity(grid, 10);
  }

  printGrid(grid);
}
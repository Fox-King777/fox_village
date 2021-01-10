#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int solve2(vector<vector<int>>& grid, vector<vector<bool>>& orig_mark, vector<vector<bool>>& mark,
           int sr, int sc, int color1, int color2) {
  vector<int> dirr = {1, -1, 0, 0};
  vector<int> dirc = {0, 0, 1, -1};

  queue<pair<int, int>> q;
  q.push(make_pair(sr, sc));
  mark[sr][sc] = true;

  int neighbor_cells = 0;
  while (!q.empty()) {
    pair<int, int> v = q.front();
    q.pop();
    neighbor_cells++;

    for (int i = 0; i < 4; ++i) {
      if (v.first + dirr[i] < grid.size() && v.first + dirr[i] >= 0 &&
          v.second + dirc[i] < grid[0].size() && v.second + dirc[i] >= 0 &&
          !mark[v.first + dirr[i]][v.second + dirc[i]] &&
          (grid[v.first + dirr[i]][v.second + dirc[i]] == color1 ||
           grid[v.first + dirr[i]][v.second + dirc[i]] == color2)) {
        q.push(make_pair(v.first + dirr[i], v.second + dirc[i]));
        mark[v.first + dirr[i]][v.second + dirc[i]] = true;
        if (grid[v.first + dirr[i]][v.second + dirc[i]] == color1) {
          orig_mark[v.first + dirr[i]][v.second + dirc[i]] = true;
        }
      }
    }
  }

  return neighbor_cells;
}

pair<int, int> solve(vector<vector<int>>& grid, vector<vector<bool>>& orig_mark, int sr, int sc,
                     int color) {
  vector<int> dirr = {1, -1, 0, 0};
  vector<int> dirc = {0, 0, 1, -1};

  queue<pair<int, int>> q;
  q.push(make_pair(sr, sc));
  vector<vector<bool>> mark(grid.size(), vector<bool>(grid[0].size(), false));
  mark[sr][sc] = true;

  int num_cells = 0;
  set<pair<int, int>> neighbhor_pos;
  while (!q.empty()) {
    pair<int, int> v = q.front();
    q.pop();
    num_cells++;

    for (int i = 0; i < 4; ++i) {
      if (v.first + dirr[i] < grid.size() && v.first + dirr[i] >= 0 &&
          v.second + dirc[i] < grid[0].size() && v.second + dirc[i] >= 0 &&
          !mark[v.first + dirr[i]][v.second + dirc[i]]) {
        if (grid[v.first + dirr[i]][v.second + dirc[i]] == color) {
          q.push(make_pair(v.first + dirr[i], v.second + dirc[i]));
          mark[v.first + dirr[i]][v.second + dirc[i]] = true;
          orig_mark[v.first + dirr[i]][v.second + dirc[i]] = true;
        } else {
          neighbhor_pos.insert(make_pair(v.first + dirr[i], v.second + dirc[i]));
        }
      }
    }
  }

  int neighbor_cells = 0;
  for (auto e : neighbhor_pos) {
    neighbor_cells = max(neighbor_cells, solve2(grid, orig_mark, mark, e.first, e.second, color,
                                                grid[e.first][e.second]));
  }

  return make_pair(num_cells, num_cells + neighbor_cells);
}

int main() {
  ifstream fin("testdata/multiplayer_moo/6.in", ifstream::in);

  int n;
  fin >> n;

  vector<vector<int>> grid(n, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      fin >> grid[i][j];
    }
  }

  vector<vector<bool>> mark(n, vector<bool>(n, false));
  int max_one = 0;
  int max_two = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (!mark[i][j]) {
        // floodfill
        pair<int, int> result = solve(grid, mark, i, j, grid[i][j]);
        max_one = max(max_one, result.first);
        max_two = max(max_two, result.second);
      }
    }
  }

  cout << max_one << endl << max_two;
}
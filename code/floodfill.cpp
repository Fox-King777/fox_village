#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void floodfill(vector<vector<int>>& grid, vector<vector<bool>>& mark, pair<int, int> spoint,
               int c) {
  vector<pair<int, int>> dir = {make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1),
                                make_pair(0, -1)};

  queue<pair<int, int>> q;
  q.push(spoint);
  mark[spoint.first][spoint.second] = true;
  grid[spoint.first][spoint.second] = c;

  while (!q.empty()) {
    pair<int, int> v = q.front();
    q.pop();
    for (pair<int, int> d : dir) {
      pair<int, int> npoint = make_pair(v.first + d.first, v.second + d.second);
      if (npoint.first < grid.size() && npoint.first >= 0 && npoint.second < grid[0].size() &&
          npoint.second >= 0 && !mark[npoint.first][npoint.second] &&
          grid[npoint.first][npoint.second] != -1) {
        mark[npoint.first][npoint.second] = true;
        grid[npoint.first][npoint.second] = c;
        q.push(npoint);
      }
    }
  }
}

void print_grid(vector<vector<int>>& grid) {
  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[i].size(); ++j) {
      cout << grid[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {
  vector<vector<int>> grid = {{0, 0, 0, 0, -1}, {-1, -1, -1, -1, -1}, {0, 0, -1, 0, 0}};
  vector<vector<bool>> mark(3, vector<bool>(5, false));

  int c = 1;
  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[i].size(); ++j) {
      if (!mark[i][j] && grid[i][j] != -1) {
        floodfill(grid, mark, make_pair(i, j), c);
        c++;
      }
    }
  }

  print_grid(grid);
}
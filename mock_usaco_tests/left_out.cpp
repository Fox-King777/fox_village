#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

int sum_row(vector<vector<char>>& grid, int row) {
  int sum = 0;
  for (int i = 0; i < grid[row].size(); ++i) {
    if (grid[row][i] == 'L') {
      sum++;
    }
  }
  return sum;
}

int sum_col(vector<vector<char>>& grid, int col) {
  int sum = 0;
  for (int i = 0; i < grid.size(); ++i) {
    if (grid[i][col] == 'L') {
      sum++;
    }
  }
  return sum;
}

void toggle_row(vector<vector<char>>& grid, int row) {
  for (int i = 0; i < grid[row].size(); ++i) {
    grid[row][i] == 'L' ? grid[row][i] = 'R' : grid[row][i] = 'L';
  }
}

void toggle_col(vector<vector<char>>& grid, int col) {
  for (int i = 0; i < grid.size(); ++i) {
    grid[i][col] == 'L' ? grid[i][col] = 'R' : grid[i][col] = 'L';
  }
}

int main() {
  ifstream fin("testdata/left_out/11.in", ifstream::in);

  int n;
  fin >> n;

  vector<vector<char>> grid(n, vector<char>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      fin >> grid[i][j];
    }
  }

  for (int i = 0; i < n; ++i) {
    if (grid[0][i] == 'L') {
      toggle_col(grid, i);
    }
  }

  for (int i = 0; i < n; ++i) {
    if (grid[i][0] == 'L') {
      toggle_row(grid, i);
    }
  }

  int sum = 0;
  pair<int, int> single_ans;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] == 'L') {
        sum++;
        if (sum == 1) {
          single_ans.first = i + 1;
          single_ans.second = j + 1;
        }
      }
    }
  }

  if (sum == (n - 1) * (n - 1)) {
    cout << "1 1";
    return 0;
  }

  if (sum == 0) {
    cout << -1;
    return 0;
  }

  for (int i = 0; i < n; ++i) {
    int r = sum_row(grid, i);
    if (r == n - 1) {
      cout << i + 1 << " " << 0;
      return 0;
    }
  }

  for (int i = 0; i < n; ++i) {
    int c = sum_col(grid, i);
    if (c == n - 1) {
      cout << 0 << " " << i;
      return 0;
    }
  }

  if (sum == 1) {
    cout << single_ans.first << " " << single_ans.second;
    return 0;
  }

  cout << -1;
}
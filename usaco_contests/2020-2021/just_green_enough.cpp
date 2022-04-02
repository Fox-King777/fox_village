#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>

using namespace std;

long long count_subgrids(vector<int>& h) {
  long long sum = 0;
  for (int i = 0; i < h.size(); ++i) {
    int mini = h[i];
    for (int l = 0; l <= i; ++l) {
      mini = min(mini, h[i - l]);
      sum += mini;
    }
  }
  return sum;
}

int main() {
  int n;
  cin >> n;

  vector<vector<int>> grid(n, vector<int>(n));
  vector<vector<int>> heights(n, vector<int>(n, 1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int a;
      cin >> a;
      if (a < 100) {
        grid[i][j] = 0;
      } else {
        grid[i][j] = 1;
      }

      if (i == 0) {
        heights[i][j] = grid[i][j];
      } else {
        if (grid[i][j] != 0) {
          heights[i][j] = heights[i - 1][j] + 1;
        } else {
          heights[i][j] = 0;
        }
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << heights[i][j] << " ";
    }
    cout << endl;
  }

  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    ans += count_subgrids(heights[i]);
  }

  cout << ans;
}
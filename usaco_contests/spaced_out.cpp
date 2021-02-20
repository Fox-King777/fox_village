#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<vector<int>> grid(n, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> grid[i][j];
    }
  }

  int ansr = 0;
  for (int i = 0; i < n; ++i) {
    int ar1 = 0;
    int ar2 = 0;
    for (int j = 0; j < n; ++j) {
      if (j % 2 == 0) {
        ar1 += grid[i][j];
      } else {
        ar2 += grid[i][j];
      }
    }
    ansr += max(ar1, ar2);
  }

  int ansc = 0;
  for (int i = 0; i < n; ++i) {
    int ac1 = 0;
    int ac2 = 0;
    for (int j = 0; j < n; ++j) {
    }
  }
}
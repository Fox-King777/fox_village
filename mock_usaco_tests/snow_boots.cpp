#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int main() {
  ifstream fin("testdata/snow_boots/5.in", ifstream::in);

  int n, b;
  fin >> n >> b;

  vector<long long> tiles(n);
  for (int i = 0; i < n; ++i) {
    fin >> tiles[i];
  }

  vector<pair<long long, long long>> boots(b);
  for (int i = 0; i < b; ++i) {
    fin >> boots[i].first >> boots[i].second;
  }

  vector<vector<bool>> can_get_there(n, vector<bool>(b, false));
  for (int i = 0; i < b; ++i) {
    can_get_there[0][i] = true;
  }

  vector<int> last_true(b, 0);

  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < b; ++j) {
      if (j > 0) {
        if (can_get_there[i][j - 1] && tiles[i] <= boots[j - 1].first) {
          last_true[j] = i;
          can_get_there[i][j] = true;
        }
      }
      if (tiles[i] <= boots[j].first && i - last_true[j] <= boots[j].second) {
        last_true[j] = i;
        can_get_there[i][j] = true;
      }
    }
  }

  int ans = numeric_limits<int>::max();
  for (int i = 0; i < b; ++i) {
    if (can_get_there[n - 1][i]) {
      ans = min(ans, i);
    }
  }

  cout << ans;
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=811
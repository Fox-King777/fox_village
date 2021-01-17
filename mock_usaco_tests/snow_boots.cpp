#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

/*long long solve(vector<long long>& tiles, vector<pair<long long, long long>>& boots,
                int top_boot_idx, long long tile_idx) {
  if (top_boot_idx > boots.size()) return numeric_limits<long long>::max();
  if (tile_idx == tiles.size() - 1) return top_boot_idx;

  long long ans = numeric_limits<long long>::max();
  for (int i = tile_idx + 1;
       i <= min(tile_idx + boots[top_boot_idx].second, (long long)tiles.size() - 1); ++i) {
    if (tiles[i] <= boots[top_boot_idx].first && tiles[tile_idx] <= boots[top_boot_idx].first) {
      ans = min(ans, solve(tiles, boots, top_boot_idx, i));
    }
  }
  ans = min(ans, solve(tiles, boots, top_boot_idx + 1, tile_idx));

  return ans;
}

int main() {
  ifstream fin("testdata/snow_boots/1.in", ifstream::in);

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

  cout << solve(tiles, boots, 0, 0);
}*/

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
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> uncomfy_cow(vector<vector<bool>>& grid, pair<int, int> p) {
  vector<int> dirx = {1, -1, 0, 0};
  vector<int> diry = {0, 0, 1, -1};

  int adj = 0;
  for (int i = 0; i < 4; ++i) {
    if (grid[p.first + dirx[i]][p.second + diry[i]]) {
      adj++;
    }
  }

  if (adj == 3) {
    for (int i = 0; i < 4; ++i) {
      pair<int, int> next = make_pair(p.first + dirx[i], p.second + diry[i]);
      if (!grid[next.first][next.second]) {
        return next;
      }
    }
  }

  return make_pair(-4000, -4000);
}

int main() {
  int n;
  cin >> n;
  vector<vector<bool>> grid(3000, vector<bool>(3000, false));

  vector<int> dirx = {1, -1, 0, 0};
  vector<int> diry = {0, 0, 1, -1};
  int total_cow = 0;
  queue<pair<int, int>> q;
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    x += 1000;
    y += 1000;
    q.push(make_pair(x, y));

    while (!q.empty()) {
      pair<int, int> v = q.front();
      q.pop();

      if (grid[v.first][v.second]) {
        continue;
      }

      total_cow++;
      grid[v.first][v.second] = true;
      if (uncomfy_cow(grid, v).first != -4000) {
        q.push(uncomfy_cow(grid, v));
      }

      for (int j = 0; j < 4; ++j) {
        if (grid[v.first + dirx[j]][v.second + diry[j]]) {
          if (uncomfy_cow(grid, make_pair(v.first + dirx[j], v.second + diry[j])).first != -4000) {
            q.push(uncomfy_cow(grid, make_pair(v.first + dirx[j], v.second + diry[j])));
          }
        }
      }
    }
    cout << total_cow - i - 1 << endl;
  }
}
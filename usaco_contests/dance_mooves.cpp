#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int main() {
  int n, k;
  cin >> n >> k;

  vector<set<pair<int, int>>> adjacency(n + 1);
  for (int i = 1; i <= n; ++i) {
    adjacency[i].insert(make_pair(i, 0));
  }

  for (int i = 1; i <= k; ++i) {
    int a, b;
    cin >> a >> b;
    adjacency[a].insert(make_pair(b, i));
    adjacency[b].insert(make_pair(a, i));
  }

  for (int i = 1; i <= n; ++i) {
    queue<pair<int, int>> q;
    vector<vector<bool>> mark(n + 1, vector<bool>(k + 1, false));

    q.push(make_pair(i, 1));
    mark[i][1] = true;
    while (!q.empty()) {
      pair<int, int> v = q.front();
      q.pop();
      for (auto ne : adjacency[v.first]) {
        if (!mark[ne.first][ne.second] && ne.second == v.second && ne.second != 0) {
          mark[ne.first][ne.second] = true;
          ne.second++;
          if (ne.second > k) {
            ne.second -= k;
          }
          q.push(ne);
          adjacency[i].insert(ne);
        }
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    cout << adjacency[i].size() << endl;
    for (auto e : adjacency[i]) {
      cout << e.first << " " << e.second << endl;
    }
    cout << endl;
  }
}
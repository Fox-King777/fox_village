#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int main() {
  ifstream fin("testdata/mootube/1.in", ifstream::in);

  int n, q;
  fin >> n >> q;

  vector<vector<int>> adjacency(n, vector<int>(n, 0));
  for (int i = 0; i < n - 1; ++i) {
    int a, b, r;
    fin >> a >> b >> r;
    a--;
    b--;

    adjacency[a][b] = r;
    adjacency[b][a] = r;
  }

  vector<pair<int, int>> questions(q);
  for (int i = 0; i < q; ++i) {
    fin >> questions[i].first >> questions[i].second;
  }

  for (int i = 0; i < q; ++i) {
    int ans = 0;
    for (int j = 0; j < n; ++j) {
      if (j != questions[i].first - 1) {
        if (adjacency[questions[i].first - 1][j] != 0) {
          if (adjacency[questions[i].first - 1][j] >= questions[i].second) {
            ans++;
          }
        }
      }
    }
    cout << ans << endl;
  }
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=788
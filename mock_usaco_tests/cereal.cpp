#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int main() {
  ifstream fin("testdata/cereal/10.in", ifstream::in);
  int n, m;
  fin >> n >> m;

  vector<pair<int, int>> cowp(n);
  for (int i = 0; i < n; ++i) {
    fin >> cowp[i].first >> cowp[i].second;
    cowp[i].first--;
    cowp[i].second--;
  }

  vector<int> rev_ans;
  vector<int> possesion(m, 0);
  int ans = 0;
  for (int i = n - 1; i >= 0; --i) {
    int j = i;
    int take = cowp[j].first;
    while (true) {
      ans++;
      if (possesion[take] == 0) {
        possesion[take] = j;
        break;
      } else if (possesion[take] < j) {
        break;
      } else {
        ans--;
        int prev = possesion[take];
        possesion[take] = j;
        if (take == cowp[prev].second) {
          break;
        }
        j = prev;
        take = cowp[j].second;
      }
    }
    rev_ans.push_back(ans);
  }

  for (int i = n - 1; i >= 0; --i) {
    cout << rev_ans[i] << endl;
  }
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=1039
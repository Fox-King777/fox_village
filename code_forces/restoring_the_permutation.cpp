#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void solve() {
  int n;
  cin >> n;

  vector<int> q(n);
  for (int i = 0; i < n; ++i) {
    cin >> q[i];
  }

  set<int> min_set;
  set<int> max_set;
  for (int i = 1; i < q[0]; ++i) {
    min_set.insert(i);
    max_set.insert(i);
  }

  vector<int> min_ans(n);
  vector<int> max_ans(n);
  min_ans[0] = q[0];
  max_ans[0] = q[0];
  for (int i = 1; i < n; ++i) {
    if (q[i] != q[i - 1]) {
      min_ans[i] = q[i];
      max_ans[i] = q[i];

      for (int j = q[i - 1] + 1; j < q[i]; ++j) {
        min_set.insert(j);
        max_set.insert(j);
      }
    } else {
      set<int>::iterator it = max_set.end();
      it--;

      min_ans[i] = *min_set.begin();
      max_ans[i] = *it;
      min_set.erase(min_set.begin());
      max_set.erase(it);
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << min_ans[i] << " ";
  }
  cout << endl;

  for (int i = 0; i < n; ++i) {
    cout << max_ans[i] << " ";
  }
  cout << endl;
}

int main() {
  int t;
  cin >> t;

  for (int i = 0; i < t; ++i) {
    solve();
  }
}
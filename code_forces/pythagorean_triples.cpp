#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

void solve() {
  int n;
  cin >> n;

  int ans = 0;
  for (int i = 3; sqrt(pow(i, 2) + pow((pow(i, 2) - 1) / 2, 2)) <= n; i += 2) {
    ans++;
  }

  cout << ans << endl;
}

int main() {
  int t;
  cin >> t;

  for (int i = 0; i < t; ++i) {
    solve();
  }
}
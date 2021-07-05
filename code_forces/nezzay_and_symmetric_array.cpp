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

bool recur(set<long long, greater<long long>>& d, long long sum, int id) {
  if (id == 0) {
    return true;
  }

  if ((*d.begin() - sum) % (id * 2) > 0 || (*d.begin() - sum) <= 0) {
    return false;
  }

  long long v = ((*d.begin() - sum) / (id * 2));
  d.erase(d.begin());
  return recur(d, sum + (2 * v), id - 1);
}

void solve() {
  int n;
  cin >> n;

  set<long long, greater<long long>> d;

  // beginning simple condition checks
  map<long long, int> cnt;
  for (int i = 0; i < 2 * n; ++i) {
    long long num;
    cin >> num;
    d.insert(abs(num));

    if (cnt.find(num) == cnt.end()) {
      cnt.insert(make_pair(num, 1));
    } else {
      cnt[num]++;
    }
  }

  for (auto const& e : cnt) {
    if (e.second != 2) {
      cout << "NO" << endl;
      return;
    }
  }

  if (recur(d, 0, d.size())) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }
}

int main() {
  int t;
  cin >> t;

  for (int i = 0; i < t; ++i) {
    solve();
  }
}
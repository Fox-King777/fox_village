#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
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
  string s, c;
  cin >> s >> c;

  if (s < c) {
    cout << s << endl;
    return;
  }

  vector<char> S;
  for (int i = 0; i < s.length(); ++i) {
    S.push_back(s[i]);
  }
  vector<char> C;
  for (int i = 0; i < c.length(); ++i) {
    C.push_back(c[i]);
  }
  vector<char> sorted = S;
  sort(sorted.begin(), sorted.end());

  bool ok = true;
  for (int i = 0; i < s.length(); ++i) {
    if (!ok) {
      break;
    }
    if (s[i] != sorted[i]) {
      for (int j = s.length() - 1; j > i; --j) {
        if (s[j] == sorted[i]) {
          swap(s[i], s[j]);
          ok = false;
          break;
        }
      }
    }
  }

  if (s < c) {
    cout << s << endl;
  } else {
    cout << "---" << endl;
  }
}

int main() {
  int t;
  cin >> t;

  for (int i = 0; i < t; ++i) {
    solve();
  }
}
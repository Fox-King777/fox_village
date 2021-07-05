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

void solve() {
  int n;
  cin >> n;

  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      if (n % 2 == 1) {
        if (j - i <= n / 2) {
          cout << 1 << " ";
        } else if (j - i > n / 2) {
          cout << -1 << " ";
        }
      } else {
        if (j - i < n / 2) {
          cout << 1 << " ";
        } else if (j - i == n / 2) {
          cout << 0 << " ";
        } else if (j - i > n / 2) {
          cout << -1 << " ";
        }
      }
    }
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
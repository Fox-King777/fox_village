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
  int n, k;
  cin >> n >> k;
  n -= k - 3;

  for (int i = 0; i < k - 3; i++) {
    cout << 1 << " ";
  }

  if (n % 2 == 1) {
    cout << 1 << " " << n / 2 << " " << n / 2 << endl;
  } else if (n == 4) {
    cout << "1 1 2" << endl;
  } else {
    if (n % 4 == 0) {
      cout << n / 4 << " " << n / 4 << " " << n / 2 << endl;
    } else {
      n /= 2;
      cout << 2 << " " << 2 * (n / 2) << " " << 2 * (n / 2) << endl;
    }
  }
}

int main() {
  int t;
  cin >> t;

  for (int i = 0; i < t; ++i) {
    solve();
  }
}
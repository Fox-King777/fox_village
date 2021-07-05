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

int main() {
  int t;
  cin >> t;

  for (int i = 0; i < t; ++i) {
    int n;
    int d[4];
    cin >> n >> d[0] >> d[1] >> d[2] >> d[3];
    if (n != 2) {
      bool yes = true;
      for (int j = 0; j < 4; ++j) {
        if (d[j] == 1) {
          if ((d[(j + 1) % 4] == n && d[(j + 3) % 4] == n) ||
              (d[(j + 2) % 4] == 1 && d[(j + 1) % 4] + d[(j + 3) % 4] == 2 * n - 1) ||
              (d[(j + 2) % 4] == 0 && d[(j + 1) % 4] == n - 1 && d[(j + 3) % 4] == n - 1)) {
            cout << "NO" << endl;
            yes = false;
            break;
          }
        } else if (d[j] == 0) {
          if ((d[(j + 1) % 4] == n || d[(j + 3) % 4] == n) ||
              (d[(j + 2) % 4] == 0 && (d[(j + 1) % 4] == n - 1 || d[(j + 3) % 4] == n - 1))) {
            cout << "NO" << endl;
            yes = false;
            break;
          }
        }
      }
      if (yes) {
        cout << "YES" << endl;
      }
    } else {
      if ((d[0] + d[1] + d[2] + d[3] == 0) || (d[0] + d[1] + d[2] + d[3] == 8) ||
          (d[0] == 1 && d[1] == 1 && d[2] == 1 && d[3] == 1)) {
        cout << "YES" << endl;
        continue;
      }
      bool no = true;
      for (int j = 0; j < 4; ++j) {
        if (d[j] == 1) {
          if ((d[(j + 1) % 4] + d[(j + 3) % 4] == 1 && d[(j + 2) % 4] == 0) ||
              (d[(j + 2) % 4] + d[j] == 3 && d[(j + 1) % 4] + d[(j + 3) % 4] == 3) ||
              (d[(j + 2) % 4] == 1 && ((d[(j + 1) % 4] == 0 && d[(j + 3) % 4] == 2) ||
                                       (d[(j + 1) % 4] == 2 && d[(j + 3) % 4] == 0)))) {
            cout << "YES" << endl;
            no = false;
            break;
          }
        }
      }
      if (no) {
        cout << "NO" << endl;
      }
    }
  }
}
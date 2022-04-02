#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int main() {
  string s;
  int q;
  cin >> s >> q;

  vector<vector<int>> presum(3, vector<int>(s.size(), 0));
  int csum = 0, osum = 0, wsum = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == 'C') {
      csum++;
    }
    if (s[i] == 'O') {
      osum++;
    }
    if (s[i] == 'W') {
      wsum++;
    }
    presum[0][i] = csum;
    presum[1][i] = osum;
    presum[2][i] = wsum;
  }

  for (int i = 0; i < q; ++i) {
    int l, r;
    cin >> l >> r;
    int ccount, ocount, wcount;
    if (l - 2 >= 0) {
      ccount = presum[0][r - 1] - presum[0][l - 2], ocount = presum[1][r - 1] - presum[1][l - 2],
      wcount = presum[2][r - 1] - presum[2][l - 2];
    } else {
      ccount = presum[0][r - 1], ocount = presum[1][r - 1], wcount = presum[2][r - 1];
    }

    if ((ccount % 2 == 1 && ocount % 2 == 0 && wcount % 2 == 0) ||
        (ccount % 2 == 0 && ocount % 2 == 1 && wcount % 2 == 1)) {
      cout << "Y";
    } else {
      cout << "N";
    }
  }
}
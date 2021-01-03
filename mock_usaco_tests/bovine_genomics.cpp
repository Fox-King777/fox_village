#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

set<string> set_intersect(const set<string>& a, const set<string>& b) {
  set<string> intersection;
  for (auto x : a) {
    if (b.find(x) != b.end()) {
      intersection.insert(x);
    }
  }
  return intersection;
}

int main() {
  ifstream fin("testdata/bovine_genomics/10.in", ifstream::in);

  int n, m;
  fin >> n >> m;

  vector<string> spotty(n);
  vector<string> plain(n);
  for (int i = 0; i < n; ++i) {
    fin >> spotty[i];
  }
  for (int i = 0; i < n; ++i) {
    fin >> plain[i];
  }

  int ans = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = i + 1; j < m; ++j) {
      for (int k = j + 1; k < m; ++k) {
        set<string> spotty_set;
        for (int s = 0; s < n; ++s) {
          string spotty_str = "";
          spotty_str += spotty[s][i];
          spotty_str += spotty[s][j];
          spotty_str += spotty[s][k];
          spotty_set.insert(spotty_str);
        }

        set<string> plain_set;
        for (int s = 0; s < n; ++s) {
          string plain_str = "";
          plain_str += plain[s][i];
          plain_str += plain[s][j];
          plain_str += plain[s][k];
          plain_set.insert(plain_str);
        }

        if (set_intersect(spotty_set, plain_set).empty()) {
          ans++;
        }
      }
    }
  }

  cout << ans;
}
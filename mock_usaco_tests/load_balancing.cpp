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

struct Point {
  long long x, y;
};

bool point_cmp(Point a, Point b) { return a.x < b.x; }

int main() {
  ifstream fin("testdata/load_balancing/1.in", ifstream::in);

  int n;
  fin >> n;

  vector<Point> cows(n);
  for (int i = 0; i < n; ++i) {
    fin >> cows[i].x >> cows[i].y;
  }
  sort(cows.begin(), cows.end(), point_cmp);

  int ans = n;
  for (int i = 0; i < n; ++i) {
    vector<Point> above;
    vector<Point> below;
    for (int j = 0; j < n; ++j) {
      if (cows[j].y <= cows[i].y) {
        below.push_back(cows[j]);
      } else {
        above.push_back(cows[j]);
      }
    }

    int be_id = 0;
    int ab_id = 0;
    while (be_id < below.size() || ab_id < above.size()) {
      long long x_line = numeric_limits<long long>::max();
      if (be_id < below.size()) {
        x_line = min(x_line, below[be_id].x);
      }
      if (ab_id < above.size()) {
        x_line = min(x_line, above[ab_id].x);
      }

      while (be_id < below.size() && below[be_id].x == x_line) {
        be_id++;
      }
      while (ab_id < above.size() && above[ab_id].x == x_line) {
        ab_id++;
      }
      ans = min(ans,
                max(max(be_id, (int)below.size() - be_id), max(ab_id, (int)above.size() - ab_id)));
    }
  }

  cout << ans;
}
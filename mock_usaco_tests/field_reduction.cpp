#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>

using namespace std;

struct Point {
  int x, y;
};

bool point_cmpx(Point a, Point b) { return a.x < b.x; }

bool point_cmpy(Point a, Point b) { return a.y < b.y; }

bool is_valid(vector<Point>& cows, int minx, int miny, int maxx, int maxy) {
  int out = 0;
  for (int i = 0; i < cows.size(); ++i) {
    if (cows[i].x < minx || cows[i].x > maxx || cows[i].y < miny || cows[i].y > maxy) {
      out++;
    }
  }

  return out <= 3;
}

int main() {
  ifstream fin("testdata/field_reduction/10.in", ifstream::in);

  int n;
  fin >> n;

  vector<Point> cows(n);
  for (int i = 0; i < n; ++i) {
    fin >> cows[i].x >> cows[i].y;
  }

  vector<Point> minx;
  vector<Point> maxx;
  sort(cows.begin(), cows.end(), point_cmpx);
  for (int i = 0; i < 4; ++i) {
    minx.push_back(cows[i]);
    maxx.push_back(cows[cows.size() - 1 - i]);
  }

  vector<Point> miny;
  vector<Point> maxy;
  sort(cows.begin(), cows.end(), point_cmpy);
  for (int i = 0; i < 4; ++i) {
    miny.push_back(cows[i]);
    maxy.push_back(cows[cows.size() - 1 - i]);
  }

  int ans = numeric_limits<int>::max();
  for (int a = 0; a < 4; ++a) {
    for (int b = 0; b < 4; ++b) {
      for (int c = 0; c < 4; ++c) {
        for (int d = 0; d < 4; ++d) {
          if (is_valid(cows, minx[a].x, miny[b].y, maxx[c].x, maxy[d].y)) {
            ans = min(ans, (maxx[c].x - minx[a].x) * (maxy[d].y - miny[b].y));
          }
        }
      }
    }
  }

  cout << ans;
}
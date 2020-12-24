#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Point {
  int x, y;
};

bool point_cmp(Point a, Point b) { return a.y > b.y; }

int solve(vector<Point>& points, vector<Point>& not_taken, int curpoint_index, int maxx, int maxy,
          int minx, int miny) {
  if (curpoint_index == points.size()) {
    /*
    for (Point e : points) {
      bool found = false;
      for (Point f : not_taken) {
        if (e.x == f.x && e.y == f.y) {
          found = true;
        }
      }
      if (!found) {
        cout << e.x << " " << e.y << endl;
      }
    }
    cout << endl;
    */
    return 1;
  }

  int ans = 0;
  bool can_take = true;
  for (int i = 0; i < not_taken.size(); ++i) {
    if ((min(minx, points[curpoint_index].x) < not_taken[i].x &&
         max(maxx, points[curpoint_index].x) > not_taken[i].x) &&
        (max(maxy, points[curpoint_index].y) > not_taken[i].y &&
         min(miny, points[curpoint_index].y) < not_taken[i].y)) {
      can_take = false;
    }
  }

  if (can_take) {
    ans += solve(points, not_taken, curpoint_index + 1, max(maxx, points[curpoint_index].x),
                 max(maxy, points[curpoint_index].y), min(minx, points[curpoint_index].x),
                 min(miny, points[curpoint_index].y));
  }
  not_taken.push_back(points[curpoint_index]);
  ans += solve(points, not_taken, curpoint_index + 1, maxx, maxy, minx, miny);
  not_taken.erase(not_taken.begin() + not_taken.size() - 1);

  return ans;
}

int main() {
  int n;
  cin >> n;

  vector<Point> points(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    points[i].x = x;
    points[i].y = y;
  }
  sort(points.begin(), points.end(), point_cmp);

  vector<Point> not_taken;
  cout << endl;
  cout << solve(points, not_taken, 0, -1, -1, numeric_limits<int>::max(),
                numeric_limits<int>::max());
}
/*
4
0 2
1 0
2 3
3 5

13
*/
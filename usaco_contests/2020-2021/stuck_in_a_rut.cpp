#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
  int x, y;
  int index;
};

bool e_cmp(Point a, Point b) { return a.y < b.y; }

bool n_cmp(Point a, Point b) { return a.x < b.x; }

int main() {
  int n;
  cin >> n;

  vector<Point> epoints;
  vector<Point> npoints;
  for (int i = 0; i < n; ++i) {
    char dir;
    cin >> dir;

    Point point;
    point.index = i;
    cin >> point.x >> point.y;
    if (dir == 'N') {
      npoints.push_back(point);
    } else {
      epoints.push_back(point);
    }
  }
  sort(epoints.begin(), epoints.end(), e_cmp);
  sort(npoints.begin(), npoints.end(), n_cmp);

  vector<int> blame(n, 0);
  vector<bool> blocked(n, false);
  for (Point e : epoints) {
    for (Point n : npoints) {
      if (!blocked[n.index] && !blocked[e.index] && n.x > e.x && n.y < e.y) {
        if (n.x - e.x < e.y - n.y) {  // e blocks n
          blame[e.index] += blame[n.index] + 1;
          blocked[n.index] = true;
        } else if (n.x - e.x > e.y - n.y) {  // n blocks e
          blame[n.index] += blame[e.index] + 1;
          blocked[e.index] = true;
        }
      }
    }
  }

  for (int ans : blame) {
    cout << ans << endl;
  }
}
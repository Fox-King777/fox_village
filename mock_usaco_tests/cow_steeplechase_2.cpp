#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Point {
  long long x, y;
};

struct Segment {
  Point p, q;
  int index;
};

bool onSegment(Point p, Point q, Point r) {
  if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
    return true;

  return false;
}

int ori(Point p, Point q, Point r) {
  int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

  if (val == 0) {
    return 0;
  }
  return (val > 0) ? 1 : 2;  // 1 = clockwise, 2 = counterclockwise
}

bool intersect(Segment a, Segment b) {
  int o1 = ori(a.p, a.q, b.p);
  int o2 = ori(a.p, a.q, b.q);
  int o3 = ori(b.p, b.q, a.p);
  int o4 = ori(b.p, b.q, a.q);

  if (o1 != o2 && o3 != o4) {
    return true;
  }

  if (o1 == 0 && onSegment(a.p, b.p, a.q)) {
    return true;
  }

  if (o2 == 0 && onSegment(a.p, b.q, a.q)) {
    return true;
  }

  if (o3 == 0 && onSegment(b.p, a.p, b.q)) {
    return true;
  }

  if (o4 == 0 && onSegment(b.p, a.q, b.q)) {
    return true;
  }

  return false;
}

bool seg_cmp(Segment a, Segment b) { return a.p.x != b.p.x ? a.p.x < b.p.x : a.p.y < b.p.y; }

int main() {
  ifstream fin("testdata/cow_steeplechase_2/7.in", ifstream::in);

  int n;
  fin >> n;

  vector<Segment> segments(n);
  for (int i = 0; i < n; ++i) {
    fin >> segments[i].p.x >> segments[i].p.y >> segments[i].q.x >> segments[i].q.y;
    segments[i].index = i;
  }
  sort(segments.begin(), segments.end(), seg_cmp);

  vector<int> num_inter(n, 0);
  set<int> active;
  for (int i = 0; i < n; ++i) {
    set<int>::iterator it = active.begin();
    while (it != active.end()) {
      if (segments[i].p.x > segments[*it].q.x) {
        active.erase(it);
      }
      ++it;
    }

    set<int>::iterator it2 = active.begin();
    while (it2 != active.end()) {
      if (intersect(segments[i], segments[*it2])) {
        num_inter[segments[i].index]++;
        num_inter[segments[*it2].index]++;
        if (num_inter[segments[i].index] > 1) {
          cout << segments[i].index + 1;
          return 0;
        }
        if (num_inter[segments[*it2].index] > 1) {
          cout << segments[*it2].index + 1;
          return 0;
        }
      }
      ++it2;
    }
    active.insert(i);
  }

  for (int i = 0; i < n; ++i) {
    if (num_inter[i] == 1) {
      cout << i + 1;
      return 0;
    }
  }
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=943
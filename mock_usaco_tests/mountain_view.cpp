#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Mountain {
  int x, y;
};

bool mountain_cmp(Mountain a, Mountain b) {
  if (a.x - a.y != b.x - b.y) {
    return a.x - a.y < b.x - b.y;
  } else {
    return a.x + a.y > b.x + b.y;
  }
}

int main() {
  ifstream fin("testdata/mountain_view/10.in", ifstream::in);

  int n;
  fin >> n;

  vector<Mountain> mountains(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    fin >> x >> y;
    mountains[i].x = x;
    mountains[i].y = y;
  }

  sort(mountains.begin(), mountains.end(), mountain_cmp);

  int ans = 0;
  int maxp = -1;
  for (int i = 0; i < n; ++i) {
    if (maxp < mountains[i].x + mountains[i].y) {
      maxp = mountains[i].x + mountains[i].y;
    }

    if (mountains[i].x + mountains[i].y >= maxp) {
      ans++;
    }
  }

  cout << ans << endl;
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=896
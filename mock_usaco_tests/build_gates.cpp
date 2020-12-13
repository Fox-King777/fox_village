#include <stdlib.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct point {
  int r, c;
};

void floodfill(vector<vector<bool>>& is_fence, int r, int c, int n) {
  queue<point> q;
  point initial;
  initial.r = r;
  initial.c = c;
  q.push(initial);

  while (!q.empty()) {
    point v = q.front();
    q.pop();
    if (v.r - 1 >= 0 && !is_fence[v.r - 1][v.c]) {
      point p = v;
      p.r--;
      q.push(p);
      is_fence[v.r - 1][v.c] = true;
    }
    if (v.r + 1 < 4 * n + 1 && !is_fence[v.r + 1][v.c]) {
      point p = v;
      p.r++;
      q.push(p);
      is_fence[v.r + 1][v.c] = true;
    }
    if (v.c - 1 >= 0 && !is_fence[v.r][v.c - 1]) {
      point p = v;
      p.c--;
      q.push(p);
      is_fence[v.r][v.c - 1] = true;
    }
    if (v.c + 1 < 4 * n + 1 && !is_fence[v.r][v.c + 1]) {
      point p = v;
      p.c++;
      q.push(p);
      is_fence[v.r][v.c + 1] = true;
    }
  }
}

int main() {
  ifstream fin("testdata/build_gates/9.in", ifstream::in);

  int n;
  fin >> n;

  string directions;
  fin >> directions;

  vector<vector<bool>> is_fence(4 * n + 1, vector<bool>(4 * n + 1, false));

  int r = 2 * n, c = 2 * n;
  is_fence[r][c] = true;
  for (int i = 0; i < n; ++i) {
    if (directions[i] == 'N') {
      r -= 2;
      is_fence[r + 1][c] = true;
    }
    if (directions[i] == 'S') {
      r += 2;
      is_fence[r - 1][c] = true;
    }
    if (directions[i] == 'W') {
      c -= 2;
      is_fence[r][c + 1] = true;
    }
    if (directions[i] == 'E') {
      c += 2;
      is_fence[r][c - 1] = true;
    }
    is_fence[r][c] = true;
  }

  int ans = 0;
  for (int i = 0; i < 4 * n + 1; ++i) {
    for (int j = 0; j < 4 * n + 1; ++j) {
      if (!is_fence[i][j]) {
        floodfill(is_fence, i, j, n);
        ans++;
      }
    }
  }

  if (ans == 0) {
    cout << 0 << endl;
    return 0;
  }
  cout << ans - 1 << endl;
}
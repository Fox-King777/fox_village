#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> dirr = {1, -1, 0, 0};
vector<int> dirc = {0, 0, 1, -1};

struct Blob {
  int a, p;
};

struct Cell {
  int r, c;
};

Blob bfs_floodfill(vector<vector<char>> grid, vector<vector<bool>>& marked, int n, int r, int c) {
  int a = 1, p = 0;
  queue<Cell> q;
  Cell first;
  first.r = r;
  first.c = c;
  q.push(first);
  marked[0][0] = true;

  while (!q.empty()) {
    Cell v = q.front();
    q.pop();

    for (int i = 0; i < 4; ++i) {
      if ((v.r + dirr[i] < n && v.r + dirr[i] >= 0 && v.c + dirc[i] < n && v.c + dirc[i] >= 0) &&
          grid[v.r + dirr[i]][v.c + dirc[i]] == '#') {
        if (!marked[v.r + dirr[i]][v.c + dirc[i]]) {
          a++;
          marked[v.r + dirr[i]][v.c + dirc[i]] = true;
          Cell newv = v;
          newv.r += dirr[i];
          newv.c += dirc[i];
          q.push(newv);
        }
      } else {
        p++;
      }
    }
  }

  Blob ans;
  ans.a = a;
  ans.p = p;

  return ans;
}

bool blob_cmp(Blob a, Blob b) {
  if (a.a != b.a) {
    return a.a > b.a;
  } else {
    return a.p < b.p;
  }
}

int main() {
  ifstream fin("testdata/icy_perimeter/6.in", ifstream::in);

  int n;
  fin >> n;

  vector<vector<char>> grid(n, vector<char>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      fin >> grid[i][j];
    }
  }

  vector<Blob> blobs;
  vector<vector<bool>> marked(n, vector<bool>(n, false));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] == '#' && !marked[i][j]) {
        blobs.push_back(bfs_floodfill(grid, marked, n, i, j));
      }
    }
  }

  sort(blobs.begin(), blobs.end(), blob_cmp);

  cout << blobs[0].a << " " << blobs[0].p;
}
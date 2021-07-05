#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

struct Point {
  int r, c;
};

bool win(set<string>& on) {
  vector<vector<char>> board(3, vector<char>(3, '.'));
  for (auto& e : on) {
    board[e[1] - '0' - 1][e[2] - '0' - 1] = e[0];
  }

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (board[i][j] == 'M') {
        if (i == 0 && j == 0) {
          if ((board[i][j + 1] == 'O' && board[i][j + 2] == 'O') ||
              (board[i + 1][j] == 'O' && board[i + 2][j] == 'O') ||
              (board[i + 1][j + 1] == 'O' && board[i + 2][j + 2] == 'O')) {
            return true;
          }
        }

        if (i == 0 && j == 1) {
          if (board[i + 1][j] == 'O' && board[i + 2][j] == 'O') {
            return true;
          }
        }

        if (i == 0 && j == 2) {
          if ((board[i][j - 1] == 'O' && board[i][j - 2] == 'O') ||
              (board[i + 1][j] == 'O' && board[i + 2][j] == 'O') ||
              (board[i + 1][j - 1] == 'O' && board[i + 2][j - 2] == 'O')) {
            return true;
          }
        }

        if (i == 1 && j == 0) {
          if (board[i][j + 1] == 'O' && board[i][j + 2] == 'O') {
            return true;
          }
        }

        if (i == 1 && j == 2) {
          if (board[i][j - 1] == 'O' && board[i][j - 2] == 'O') {
            return true;
          }
        }

        if (i == 2 && j == 0) {
          if ((board[i][j + 1] == 'O' && board[i][j + 2] == 'O') ||
              (board[i - 1][j] == 'O' && board[i - 2][j] == 'O') ||
              (board[i - 1][j + 1] == 'O' && board[i - 2][j + 2] == 'O')) {
            return true;
          }
        }

        if (i == 2 && j == 1) {
          if (board[i - 1][j] == 'O' && board[i - 2][j] == 'O') {
            return true;
          }
        }

        if (i == 2 && j == 2) {
          if ((board[i][j - 1] == 'O' && board[i][j - 2] == 'O') ||
              (board[i - 1][j] == 'O' && board[i - 2][j] == 'O') ||
              (board[i - 1][j - 1] == 'O' && board[i - 2][j - 2] == 'O')) {
            return true;
          }
        }
      }
    }
  }

  return false;
}

string to_string_key(int r, int c, set<string> b) {
  stringstream ss;
  ss << r << "," << c << ",";
  for (string e : b) {
    ss << e << ",";
  }
  return ss.str();
}

int main() {
  int n;
  cin >> n;

  vector<vector<string>> grid(n, vector<string>(n));
  map<string, vector<string>> need;
  Point start;
  for (int i = 0; i < n; ++i) {
    string r;
    cin >> r;
    for (int j = 0; j < 3 * n; j += 3) {
      if (r[j] == 'B') {
        grid[i][j / 3] = ".";
        start.r = i;
        start.c = j / 3;
      } else if (r[j] == 'M' || r[j] == 'O') {
        grid[i][j / 3] = r.substr(j, 3);
        vector<string> temp;
        need.insert(make_pair(r.substr(j, 3), temp));
      } else {
        grid[i][j / 3] = r[j];
      }
    }
  }

  vector<int> dirr = {1, -1, 0, 0};
  vector<int> dirc = {0, 0, 1, -1};
  queue<pair<Point, set<string>>> q;
  map<string, bool> mark;
  set<set<string>> configs;
  q.push(make_pair(start, set<string>{}));
  mark.insert(make_pair((start.r + "," + start.c + (string) ","), true));
  int ans = 0;
  while (!q.empty()) {
    pair<Point, set<string>> v = q.front();
    q.pop();
    for (int i = 0; i < 4; ++i) {
      set<string> b = v.second;
      if (grid[v.first.r + dirr[i]][v.first.c + dirc[i]] != "." &&
          grid[v.first.r + dirr[i]][v.first.c + dirc[i]] != "#") {
        string moo1 = grid[v.first.r + dirr[i]][v.first.c + dirc[i]];
        string moo2 = moo1;
        moo2[0] = moo1[0] == 'M' ? 'O' : 'M';
        if (b.find(moo1) == b.end() && b.find(moo2) == b.end()) {
          b.insert(grid[v.first.r + dirr[i]][v.first.c + dirc[i]]);
        }
      }
      string key = to_string_key(v.first.r + dirr[i], v.first.c + dirc[i], b);
      if (mark.find(key) == mark.end() && grid[v.first.r + dirr[i]][v.first.c + dirc[i]] != "#") {
        mark.insert(make_pair(key, true));
        if (win(b)) {
          if (configs.find(b) == configs.end()) {
            configs.insert(b);
            ans++;
          }
          continue;
        }
        pair<Point, set<string>> u;
        u.first.r = v.first.r + dirr[i];
        u.first.c = v.first.c + dirc[i];
        u.second = b;
        q.push(u);
      }
    }
  }

  cout << ans;
}
/*
7
#####################
###O11###...###M13###
###......O22......###
###...######M22######
###BBB###M31###M11###
###...O32...M33O31###
#####################
*/
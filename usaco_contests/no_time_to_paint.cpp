#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int how_many_strokes(string str) {
  vector<bool> mark(str.size(), false);
  int num_strokes = 0;
  for (int i = 0; i < str.size(); ++i) {
    char color = str[i];
    if (!mark[i]) {
      for (int j = i; j < str.size(); ++j) {
        if (color == str[j]) {
          mark[j] = true;
        } else if ((int)color > (int)str[j]) {
          num_strokes++;
          break;
        }

        if (j == str.size() - 1) {
          num_strokes++;
        }
      }
    }
  }

  return num_strokes;
}

int main() {
  int n, q;
  cin >> n >> q;

  string paint;
  cin >> paint;

  vector<pair<int, int>> questions(q);
  for (int i = 0; i < q; ++i) {
    cin >> questions[i].first >> questions[i].second;
  }

  for (int i = 0; i < q; ++i) {
    int ans = 0;
    if (questions[i].first > 1) {
      ans += how_many_strokes(paint.substr(0, questions[i].first - 1));
    }
    ans += how_many_strokes(paint.substr(questions[i].second, paint.size() - questions[i].second));
    cout << ans << endl;
  }
}
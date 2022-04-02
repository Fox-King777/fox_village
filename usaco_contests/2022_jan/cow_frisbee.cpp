#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

struct cow {
  int h, index;
};

int main() {
  int n;
  cin >> n;

  stack<cow> line;
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    cow a;
    cin >> a.h;
    a.index = i;

    while (!line.empty() && line.top().h < a.h) {
      ans += a.index - line.top().index + 1;
      line.pop();
    }
    if (!line.empty()) {
      ans += a.index - line.top().index + 1;
    }
    line.push(a);
  }

  cout << ans;
}

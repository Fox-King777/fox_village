#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct cow {
  long long a, t, s;
};

struct scmp {
  bool operator()(cow const& a, cow const& b) { return a.s > b.s; }
};

bool acmp(cow a, cow b) {
  if (a.a != b.a) {
    return a.a < b.a;
  } else {
    return a.s < b.s;
  }
}

int main() {
  ifstream fin("testdata/convention2/5.in", ifstream::in);

  int n;
  fin >> n;

  vector<cow> cows(n);
  for (int i = 0; i < n; ++i) {
    fin >> cows[i].a >> cows[i].t;
    cows[i].s = i;
  }
  sort(cows.begin(), cows.end(), acmp);

  long long ans = 0;
  int index = 0;
  long long time = 0;
  priority_queue<cow, vector<cow>, scmp> w;
  for (int i = 0; i < n; ++i) {
    if (w.empty()) {
      w.push(cows[index]);
      time = cows[index].a;
      index++;
    }
    cow ncow = w.top();
    w.pop();

    ans = max(ans, time - ncow.a);
    time += ncow.t;

    while (index < n && cows[index].a <= time) {
      w.push(cows[index]);
      index++;
    }
  }

  cout << ans;
}
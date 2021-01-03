#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Cow {
  int a;
  int t;
  int sen;

  // Operator overrides.
  bool operator<(const Cow& rhs) const { return this->sen > rhs.sen; }
};

bool cow_cmp(Cow a, Cow b) {
  if (a.a != b.a) {
    return a.a < b.a;
  } else {
    return a.sen < b.sen;
  }
}

int main() {
  ifstream fin("testdata/convention2/9.in", ifstream::in);

  int n;
  fin >> n;

  vector<Cow> cows(n);
  for (int i = 0; i < n; ++i) {
    fin >> cows[i].a >> cows[i].t;
    cows[i].sen = i;
  }

  sort(cows.begin(), cows.end(), cow_cmp);

  int k = 0;
  int time = 0;
  int ans = 0;
  priority_queue<Cow> q;
  for (int i = 0; i < n; ++i) {
    if (q.empty()) {
      q.push(cows[k]);
      time = cows[k].a;
      k++;
    }

    Cow cur_cow = q.top();
    q.pop();

    ans = min(ans, time - cur_cow.a);

    while (k < n && cows[k].a <= time + cur_cow.t) {
      q.push(cows[k++]);
    }
    time += cur_cow.t;
  }

  cout << ans;
}
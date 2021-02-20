#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Cow {
  int num, val;
};

bool cow_cmp(Cow a, Cow b) { return a.val < b.val; }

int main() {
  ifstream fin("testdata/paired_up/2.in", ifstream::in);

  int n, m = 0;
  fin >> n;

  vector<Cow> cows(n);
  for (int i = 0; i < n; ++i) {
    fin >> cows[i].num >> cows[i].val;
    m += cows[i].num;
  }
  sort(cows.begin(), cows.end(), cow_cmp);

  int ans = numeric_limits<int>::min();
  while (m > 0) {
    if (cows[0].num == 0) {
      cows.erase(cows.begin());
    }
    if (cows[cows.size() - 1].num == 0) {
      cows.erase(cows.begin() + cows.size() - 1);
    }

    if (ans < cows[0].val + cows[cows.size() - 1].val) {
      ans = cows[0].val + cows[cows.size() - 1].val;
    }

    int minimum = min(cows[0].num, cows[cows.size() - 1].num);
    cows[0].num -= minimum;
    cows[cows.size() - 1].num -= minimum;
    m -= 2 * minimum;
  }

  cout << ans;
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=738
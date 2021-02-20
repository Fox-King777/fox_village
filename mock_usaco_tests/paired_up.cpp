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
  int start = 0, end = cows.size() - 1;
  while (m > 0) {
    if (cows[start].num == 0) {
      start++;
    }
    if (cows[end].num == 0) {
      end--;
    }

    if (ans < cows[start].val + cows[end].val) {
      ans = cows[start].val + cows[end].val;
    }

    int minimum = min(cows[start].num, cows[end].num);
    cows[start].num -= minimum;
    cows[end].num -= minimum;
    m -= 2 * minimum;
  }

  cout << ans;
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=738
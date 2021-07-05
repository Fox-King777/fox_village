#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

bool ok(vector<int>& papers, int n, int k, int l, int h) {
  int needed = 0;
  for (int i = 0; i < h; ++i) {
    needed += max(0, h - papers[i]);
  }
  if (needed > k * l) {
    return false;
  }

  for (int i = 0; i < h; ++i) {
    if (papers[i] + k < h) {
      return false;
    }
  }

  return true;
}

int main() {
  int n, k, l;
  cin >> n >> k >> l;

  vector<int> papers(n);
  for (int i = 0; i < n; ++i) {
    cin >> papers[i];
  }
  sort(papers.begin(), papers.end(), greater<int>());

  int ans = 0;
  int lo = 1, hi = n;
  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    if (ok(papers, n, k, l, mid)) {
      ans = max(ans, mid);
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }

  cout << ans;
}
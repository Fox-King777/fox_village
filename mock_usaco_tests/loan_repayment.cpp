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

bool sim(long long n, long long k, long long m, long long x) {
  long long g = 0;
  while (k > 0 && g < n) {
    long long y = (n - g) / x;
    if (y < m) {
      long long left_over_days = (n - g + m - 1) / m;
      return left_over_days <= k;
    }

    long long maxmatch = n - x * y;
    long long numdays = (maxmatch - g) / y + 1;
    if (numdays > k) numdays = k;
    g += y * numdays;
    k -= numdays;
  }

  return g >= n;
}

int main() {
  ifstream fin("testdata/loan_repayment/10.in", ifstream::in);

  long long n, k, m;
  fin >> n >> k >> m;

  long long hi = 1000000000000;
  long long lo = 1;
  long long ans = 0;
  while (lo <= hi) {
    long long mid = (lo + hi) / 2;

    if (sim(n, k, m, mid)) {
      ans = max(ans, mid);
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }

  cout << ans;
}
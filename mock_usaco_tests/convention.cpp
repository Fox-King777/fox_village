#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool check(long long r, vector<int> cow, int n, int m, int c) {
  int ccount = 0;
  int wcount = 1;
  int first = cow[0];

  for (int i = 1; i < n; ++i) {
    ccount++;
    if (cow[i] - first > r || ccount > c) {
      first = cow[i];
      wcount++;
      ccount = 1;
    }
  }

  return (wcount <= m);
}

int main() {
  ifstream fin("testdata/convention/5.in", ifstream::in);
  int n, m, c;
  fin >> n >> m >> c;

  vector<int> cow(n);
  for (int i = 0; i < n; ++i) {
    fin >> cow[i];
  }
  sort(cow.begin(), cow.end());

  long long hi = 1000000000;
  long long lo = 0;
  long long ans;

  while (lo <= hi) {
    long long mid = lo + (hi - lo) / 2;
    if (check(mid, cow, n, m, c)) {
      hi = mid - 1;
      ans = mid;
    }

    if (!check(mid, cow, n, m, c)) {
      lo = mid + 1;
    }
  }

  cout << ans;
}
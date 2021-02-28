#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int main() {
  ifstream fin("testdata/diamond_collector/1.in", ifstream::in);

  int n;
  long long k;
  fin >> n >> k;

  vector<long long> sizes(n);
  for (int i = 0; i < n; ++i) {
    fin >> sizes[i];
  }
  sort(sizes.begin(), sizes.end());

  // if i is leftmost in the case
  vector<int> first_case(n);
  int r = 0;
  for (int i = 0; i < n; ++i) {
    while (r < n && sizes[r] - sizes[i] <= k) {
      r++;
    }
    first_case[i] = r - i;
  }

  //
  vector<int> second_case(n + 1);
  second_case[n] = 0;
  for (int i = n - 1; i >= 0; --i) {
    second_case[i] = max(second_case[i + 1], first_case[i]);
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    ans = max(ans, first_case[i] + second_case[i + first_case[i]]);
  }

  cout << ans;
}
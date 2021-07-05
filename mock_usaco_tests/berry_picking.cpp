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

int main() {
  ifstream fin("testdata/berry_picking/10.in", ifstream::in);

  int n, k, b = 0;
  fin >> n >> k;

  vector<int> trees(n);
  for (int i = 0; i < n; ++i) {
    fin >> trees[i];
    b = max(b, trees[i]);
  }

  int ans = 0;
  for (int i = 1; i <= b; ++i) {
    int fbuckets = 0;
    for (int j = 0; j < n; ++j) {
      fbuckets += trees[j] / i;
    }

    if (fbuckets < k / 2) {  // not enough buckets are filled; you will get 0 berries
      break;
    }

    if (fbuckets >= k) {  // more than k filled buckets means you get i * k / 2 amount of berries
      ans = max(ans, i * (k / 2));
      continue;
    }
    // in between k / 2 and k filled buckets means you get (fill buckets - k / 2) fill
    // buckets and some extra left over
    int sum = i * (fbuckets - (k / 2));
    vector<int> left_over = trees;
    for (int j = 0; j < left_over.size(); ++j) {
      left_over[j] %= i;
    }
    sort(left_over.begin(), left_over.end(), greater<int>());
    for (int j = 0; j < left_over.size(); ++j) {
      if (fbuckets + j == k) {
        break;
      }
      sum += left_over[j];
    }
    ans = max(ans, sum);
  }

  cout << ans;
}
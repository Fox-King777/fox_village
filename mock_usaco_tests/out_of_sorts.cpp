#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Num {
  int val;
  int idx;
};

bool num_cmp(Num a, Num b) {
  if (a.val != b.val) {
    return a.val < b.val;
  } else {
    return a.idx < b.idx;
  }
}

int main() {
  ifstream fin("testdata/out_of_sorts/8.in", ifstream::in);

  int n;
  fin >> n;

  vector<Num> nums(n);
  for (int i = 0; i < n; ++i) {
    fin >> nums[i].val;
    nums[i].idx = i;
  }
  sort(nums.begin(), nums.end(), num_cmp);

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    ans = max(ans, abs(i - nums[i].idx));
  }

  cout << ans + 1;
}
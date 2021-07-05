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

void check(vector<long long>& nums, set<multiset<long long>>& all_sol, long long sum, long long b,
           long long c) {
  long long a = sum - b - c;
  if (a <= 0 || b <= 0 || c <= 0) {
    return;
  }

  set<long long> check_arr = {0, a, b, c, a + b, a + c, b + c, a + b + c};
  for (long long e : nums) {
    if (!check_arr.count(e)) {
      return;
    }
  }

  all_sol.insert({a, b, c});
}

void test(vector<long long>& nums, set<multiset<long long>>& all_sol, long long sum) {
  set<long long> possible;
  for (long long e : nums) {
    if (e > sum) {
      return;
    }
    if (e == 0 || e == sum) {
      continue;
    }
    possible.insert(min(e, sum - e));
  }

  if (possible.size() < 2) {
    return;
  }

  long long a = *possible.begin();
  long long b = *next(possible.begin());
  check(nums, all_sol, sum, a, b);
  check(nums, all_sol, sum, a, sum - b);
}

void solve() {
  int n;
  cin >> n;

  vector<long long> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  nums.push_back(0);

  set<multiset<long long>> all_sol;
  for (int i = 0; i < nums.size(); ++i) {
    for (int j = i + 1; j < nums.size(); ++j) {
      test(nums, all_sol, nums[i] + nums[j]);
    }
  }

  cout << "ans: " << all_sol.size() << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
}

/*
10
7
1 2 3 4 5 6 7
4
4 5 7 8
4
4 5 7 9
4
4 5 7 10
4
4 5 7 11
4
4 5 7 12
4
4 5 7 13
4
4 5 7 14
4
4 5 7 15
4
4 5 7 16
*/
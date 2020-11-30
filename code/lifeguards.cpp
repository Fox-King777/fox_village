#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;
using interval = pair<int, int>;

bool is_disjoint(interval a, interval b) { return a.second < b.first || b.second < a.first; }
bool contains(interval a, interval b) { return a.first <= b.first and a.second >= b.second; }

bool cows_cmp(interval a, interval b) {
  if (a.first != b.first) {
    return a.first < b.first;
  } else {
    return a.second > b.second;
  }
}

void remove_supercedes(vector<interval>& cows) {
  int max_end = numeric_limits<int>::min();
  int num_kept = 0;
  for (auto& in : cows) {
    if (in.second > max_end) {
      cows[num_kept++] = in;
    }
    max_end = max(max_end, in.second);
  }
  cows.resize(num_kept);
}

string repr(interval itv) {
  char buf[100];
  sprintf(buf, "[%d, %d]", itv.first, itv.second);
  return string(buf);
}

void print_array(int arr[], int n) {
  for (int i = 0; i < n; ++i) {
    cout << i << ":" << arr[i] << " ";
  }
}

int main() {
  ifstream fin("testdata/lifeguards/2.in", ifstream::in);
  int n, k;
  fin >> n >> k;

  vector<interval> cows;
  for (int i = 0; i < n; ++i) {
    interval input;
    fin >> input.first >> input.second;
    cows.emplace_back(input);
  }

  sort(cows.begin(), cows.end(), cows_cmp);
  remove_supercedes(cows);

  k -= (n - cows.size());

  int dp[cows.size() + 1][k + 1];
  for (int i = 0; i <= cows.size(); i++) {
    for (int j = 0; j <= k; j++) {
      dp[i][j] = 0;
    }
  }

  int j = 1;
  for (int i = 1; i <= cows.size(); ++i) {
    while (is_disjoint(cows[i - 1], cows[j - 1])) {
      j++;
    }
    for (int r = 0; r <= k; ++r) {
      // case 0
      dp[i][r] = dp[i - 1][max(0, r - 1)];
      // case 1
      if (r <= i - 1) {
        dp[i][r] = max(dp[i][r], cows[i - 1].second - cows[i - 1].first);
      }
      // case 2
      if (i > j) {
        int r0 = max(0, r - (i - j - 1));
        if (j - 1 >= r0) {
          dp[i][r] = max(dp[i][r], dp[j - 1][r0] + cows[i - 1].second - cows[j - 1].first);
        }
      }
      // case 3
      int r0 = max(0, r - (i - j));
      if (j - 1 >= r0) {
        dp[i][r] = max(dp[i][r], dp[j - 1][r0] + cows[i - 1].second - cows[i - 1].first);
      }
    }
  }

  cout << dp[cows.size()][k] << endl;
}
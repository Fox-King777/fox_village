#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

void print_vec(long vec[], int n) {
  long s = 0;
  for (int i = 0; i < n; ++i) {
    if (vec[i] > 0) {
      s += vec[i];
      cout << i << ": " << vec[i] << "," << vec[i + 1] + vec[i] << endl;
    }
  }
  cout << "s=" << s << endl;
}

int main() {
  int n, k;
  cin >> n >> k;

  pair<long, int> val[250010];
  val[0] = make_pair(0, 0);
  long sum[250010];
  memset(sum, 0, sizeof sum);

  for (int i = 1; i <= n; ++i) {
    int v;
    cin >> v;
    val[i] = make_pair(v, i);
    if (val[i].first > 0) {
      sum[i] = sum[i - 1] + val[i].first;
    } else {
      sum[i] = sum[i - 1];
    }
  }

  long dp[250010];
  dp[0] = 0;
  for (int i = 1; i <= n; ++i) {
    dp[i] = -10000000000;
  }

  priority_queue<pair<long, int>, vector<pair<long, int>>, greater<pair<long, int>>> sliding_window;

  /*for (int i = 1; i <= n; ++i) {
      for (int j = max(0, i - k); j < i; ++j) {
          if (j + 1 == i) {
               dp[i] = max(dp[i], dp[j] + val[i]);
          } else if (j == 0) {
              dp[i] = max(dp[i], 0 +  val[i] + (i > j + 1 ? sum[i - 1] - sum[j] : 0));
          } else {
              dp[i] = max(dp[i], dp[j] + val[j + 1] + val[i] + (i > j + 3 ? sum[i - 1] - sum[j + 2]
  : 0));
          }
      }
  }*/

  for (int i = 1; i <= n; ++i) {
    sliding_window.push(val[i - 1]);
    int j = sliding_window.top().second;
    if (j + 1 == i) {
      dp[i] = max(dp[i], dp[j] + val[i].first);
    } else if (j == 0) {
      dp[i] = max(dp[i], 0 + val[i].first + (i > j + 1 ? sum[i - 1] - sum[j] : 0));
    } else {
      dp[i] = max(dp[i], dp[j] + val[j + 1].first + val[i].first + (i > j + 3 ? sum[i - 1] - sum[j + 2] : 0));
    }
  }

  int answer = 0;

  for (int i = 0; i <= n; ++i) {
    if (answer < dp[i]) {
      answer = dp[i];
    }
  }

  cout << answer;
}
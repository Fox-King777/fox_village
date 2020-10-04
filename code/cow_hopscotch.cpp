#include <algorithm>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <queue>
#include <utility>
using namespace std;

const int N = 250010;

class Monoqueue {
 private:
  deque<pair<long, int> > m_deque;  // pair.first: the actual value,
                                    // pair.second: how many elements were deleted between
                                    // it and the one before it.
  int length_;

 public:
  Monoqueue() { this->length_ = 0; }
  void push(long val) {
    int count = 0;
    while (!m_deque.empty() && m_deque.back().first < val) {
      count += m_deque.back().second + 1;
      m_deque.pop_back();
    }
    m_deque.push_back(make_pair(val, count));
    ++this->length_;
  };

  long max() { return m_deque.front().first; }

  bool empty() { return this->length_ == 0; }

  void pop() {
    if (m_deque.front().second > 0) {
      m_deque.front().second--;
      return;
    }
    m_deque.pop_front();

    if (this->length_ > 0) {
      --this->length_;
    }
  }

  int length() { return this->length_; }
};

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

long hop_scotch(long val[], int n, int k) {
  long sum[N];
  memset(sum, 0, sizeof sum);

  for (int i = 1; i <= n; ++i) {
    if (val[i] > 0) {
      sum[i] = sum[i - 1] + val[i];
    } else {
      sum[i] = sum[i - 1];
    }
  }

  long dp[N];
  dp[0] = 0;
  for (int i = 1; i <= n; ++i) {
    dp[i] = -10000000000;
  }

  Monoqueue queue;

  for (int i = 1; i <= n; ++i) {
    dp[i] = max(dp[i], dp[i - 1] + val[i]);

    if (!queue.empty()) {
      dp[i] = max(dp[i], queue.max() + val[i] + sum[i - 1]);
    }
    if (queue.length() >= k - 1) {
      queue.pop();
    }

    if (i == 1) {
      queue.push(0);
    } else {
      queue.push(dp[i - 1] + val[i] - sum[i + 1]);
    }
  }

  long answer = 0;
  for (int i = 0; i <= n; ++i) {
    if (answer < dp[i]) {
      answer = dp[i];
    }
  }
  return answer;
}

int main() {
  int n, k;
  cin >> n >> k;
  long val[N];
  val[0] = 0;

  for (int i = 1; i <= n; ++i) {
    cin >> val[i];
  }

  cout << hop_scotch(val, n, k) << endl;
  return 0;
}
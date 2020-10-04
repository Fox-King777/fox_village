#include <algorithm>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <queue>
using namespace std;

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

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
  vector<int> results;
  Monoqueue mq;
  k = min(k, (int)nums.size());
  int i = 0;
  for (; i < k - 1; ++i) {  // push first k - 1 numbers;
    mq.push(nums[i]);
    results.push_back(mq.max());
  }

  for (; i < nums.size(); ++i) {
    mq.push(nums[i]);             // push a new element to queue;
    results.push_back(mq.max());  // report the current max in queue;
    mq.pop();                     // pop first element in queue;
  }
  return results;
}

int main() {
  vector<int> nums{1, 5, 2, 3, 2, 6, 7};
  vector<int> max = maxSlidingWindow(nums, 3);

  for (int i = 0; i < max.size(); ++i) {
    cout << max[i] << " ";
  }
}
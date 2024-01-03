#include <bits/stdc++.h>

#include <iostream>

using namespace std;

int max_labels_same(const int n, const int k, vector<int>& difference, set<int>& label_set) {
  vector<int> difference_freq(k, 0);
  for (int i = 1; i <= n; ++i) {
    if (difference[i] == numeric_limits<int>::min()) {
      continue;
    }
    difference_freq[difference[i]]++;
  }

  int match = numeric_limits<int>::min();
  for (auto e : difference_freq) {
    match = max(match, e);
  }

  return match + n - label_set.size();
}

int rotate(int n, int k, vector<int>& A, vector<int>& B, set<int>& label_set) {
  vector<int> difference(n + 1, numeric_limits<int>::min());
  for (int i = 1; i <= n; ++i) {
    if (B[i] != numeric_limits<int>::min() && A[i] != numeric_limits<int>::min()) {
      difference[i] = B[i] - A[i];
      if (difference[i] < 0) {
        difference[i] += k;
      }
    }
  }

  return max_labels_same(n, k, difference, label_set);
}

int main() {
  int n, k;
  cin >> n >> k;

  vector<int> A(n + 1, numeric_limits<int>::min());
  vector<int> B(n + 1, numeric_limits<int>::min());
  vector<int> B_reverse(n + 1, numeric_limits<int>::min());
  set<int> label_set;
  for (int i = 0; i < k; ++i) {
    int a;
    cin >> a;
    label_set.insert(a);
    A[a] = i;
  }
  for (int i = 0; i < k; ++i) {
    int b;
    cin >> b;
    label_set.insert(b);
    B[b] = i;
    B_reverse[b] = k - i - 1;
  }

  int res1 = rotate(n, k, A, B, label_set);
  int res2 = rotate(n, k, A, B_reverse, label_set);

  cout << max(res1, res2);
}

/*
6 3
1 2 3
3 2 1

6 4
1 2 3 4
4 3 2 5
*/
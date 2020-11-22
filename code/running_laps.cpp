#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct FenwickTree {
  vector<int> partial_sum;

  FenwickTree(int n) { partial_sum.resize(n, 0); }

  int prefix_sum(int k) {
    int s = 0;

    while (k >= 0) {
      s += partial_sum[k];
      k = this->g(k) - 1;
    }

    return s;
  }

  int range_sum(int a, int b) { return this->prefix_sum(b - 1) - this->prefix_sum(a - 1); }

  void add(int k, int val) {
    while (k < partial_sum.size()) {
      partial_sum[k] += val;
      k = this->h(k);
    }
  }

  int g(int i) { return i & (i + 1); }

  int h(int i) { return i | (i + 1); }
};

struct cow_ending_info {
  long long laps;
  long long frac;
};

bool cow_cmp(cow_ending_info a, cow_ending_info b) {
  return (a.frac < b.frac) || (a.frac == b.frac && a.laps < b.laps);
}

int main() {
  ifstream fin("testdata/running_laps/3.in", ifstream::in);
  long n, L, c;
  fin >> n >> L >> c;

  long long cows_speed[n];
  long long max_speed = 0;
  for (int i = 0; i < n; i++) {
    fin >> cows_speed[i];
    if (max_speed < cows_speed[i]) {
      max_speed = cows_speed[i];
    }
  }

  cow_ending_info cows_end[n];

  for (int i = 0; i < n; i++) {
    cows_end[i].laps = (cows_speed[i] * L) / max_speed;
    cows_end[i].frac = (cows_speed[i] * L) % max_speed;
  }

  sort(cows_end, cows_end + n, cow_cmp);

  long long sum = 0;
  FenwickTree num_cows_tree(L + 1);
  FenwickTree sum_laps_tree(L + 1);

  for (int i = 0; i < n; i++) {
    int l = cows_end[i].laps;
    int part_0 = l * num_cows_tree.range_sum(0, l) - sum_laps_tree.range_sum(0, l);
    int part_1 =
        sum_laps_tree.range_sum(l + 1, L + 1) - (l + 1) * num_cows_tree.range_sum(l + 1, L + 1);
    sum += part_0 + part_1;
    num_cows_tree.add(l, 1);
    sum_laps_tree.add(l, l);
  }

  cout << sum;
}
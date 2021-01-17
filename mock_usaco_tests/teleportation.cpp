#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

long long calculate_dis_sum(vector<pair<long long, long long>>& manure, long long tp) {
  long long sum = 0;
  for (int i = 0; i < manure.size(); ++i) {
    sum += min(abs(manure[i].first - manure[i].second),
               abs(manure[i].first) + abs(tp - manure[i].second));
  }
  return sum;
}

int main() {
  ifstream fin("testdata/teleportation/1.in", ifstream::in);

  int n;
  fin >> n;

  long long l = 100000000, r = -100000000;
  vector<pair<long long, long long>> manure(n);
  for (int i = 0; i < n; ++i) {
    fin >> manure[i].first >> manure[i].second;
    if (abs(manure[i].first) < abs(manure[i].first - manure[i].second)) {
      l = min(l, min(manure[i].first, manure[i].second));
      r = max(r, max(manure[i].first, manure[i].second));
    }
  }

  long long ans = numeric_limits<long long>::max();
  for (int i = l; i <= r; ++i) {
    ans = min(ans, calculate_dis_sum(manure, i));
  }
  cout << ans;
}
#include <bits/stdc++.h>

#include <iostream>

using namespace std;

void print_tower(unordered_map<long long, long long> tower) {
  for (auto t : tower) {
    cout << t.first << " " << t.second << ", ";
  }
  cout << endl;
}

int main() {
  long long n, m, k;
  cin >> n >> m >> k;

  vector<pair<long long, long long>> weights(n);
  for (int i = 0; i < n; ++i) {
    cin >> weights[i].first >> weights[i].second;
    weights[i].second = min(weights[i].second, m);
  }
  sort(weights.rbegin(), weights.rend());

  unordered_map<long long, long long> tower;
  long long res = 0;
  tower.insert({numeric_limits<long long>::min(), m});
  for (int i = 0; i < n; ++i) {
    long long c = 0;
    for (auto it = tower.begin(); it != tower.end();) {
      if (weights[i].first <= it->first - k) {
        long long tower_c = it->second;
        res += min(tower_c, weights[i].second);
        c += min(tower_c, weights[i].second);

        if (weights[i].second < it->second) {
          tower[it->first] -= weights[i].second;
          ++it;
        } else {
          it = tower.erase(it);
        }

        weights[i].second -= min(tower_c, weights[i].second);
      } else {
        ++it;
      }
    }
    tower.insert({weights[i].first, c});
  }

  cout << res << endl;
}
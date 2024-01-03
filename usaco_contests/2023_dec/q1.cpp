#include <bits/stdc++.h>

#include <iostream>

using namespace std;

bool combine(map<long long, long long>& tower, long long lbound) {
  map<long long, long long>::iterator it = tower.lower_bound(lbound);
  if (it == tower.end()) {
    return false;
  }

  pair<long long, long long> combined_tower;
  combined_tower.first = it->first;
  combined_tower.second = 0;
  while (it != tower.end()) {
    combined_tower.second += it->second;
    it = tower.erase(it);
  }
  tower.insert(combined_tower);
  return true;
}

int main() {
  long long n, m, k;
  cin >> n >> m >> k;

  vector<pair<long long, long long>> w(n);
  for (int i = 0; i < n; ++i) {
    cin >> w[i].first >> w[i].second;
    w[i].second = min(w[i].second, m);
  }
  sort(w.rbegin(), w.rend());

  map<long long, long long> tower;
  tower.insert({numeric_limits<long long>::max(), m});
  long long res = 0;
  for (int i = 0; i < n; ++i) {
    if (!combine(tower, w[i].first + k)) {
      continue;
    }

    if (w[i].second < tower.rbegin()->second) {
      tower.rbegin()->second -= w[i].second;
      tower.insert({w[i].first, w[i].second});
      res += w[i].second;
    } else {
      tower.insert({w[i].first, tower.rbegin()->second});
      res += tower.rbegin()->second;
      tower.erase(prev(tower.end()));
    }
  }

  cout << res << endl;
}
/*
5 5 2
10 5
7 5
6 5
5 3
4 5

3 5 2
9 4
7 6
5 5

3 5 3
5 5
7 6
9 4
*/
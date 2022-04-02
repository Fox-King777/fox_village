#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

long long find_least_cycle(vector<pair<long long, long long>>& adj, long long pos) {
  vector<bool> mark(adj.size(), false);
  long long mini = numeric_limits<long long>::max();
  while (!mark[pos]) {
    mark[pos] = true;
    mini = min(mini, adj[pos].second);
    pos = adj[pos].first;
  }
  return mini;
}

long long solve(vector<pair<long long, long long>>& adj, vector<bool>& mark,
                set<long long> ancestors, long long pos, long long sum) {
  ancestors.insert(pos);
  mark[pos] = true;
  if (ancestors.find(adj[pos].first) != ancestors.end()) {
    sum += adj[pos].second;
    return sum - find_least_cycle(adj, pos);
  } else if (mark[adj[pos].first]) {
    return sum + adj[pos].second;
  } else {
    return solve(adj, mark, ancestors, adj[pos].first, sum + adj[pos].second);
  }
}

long long solve2(vector<pair<long long, long long>>& adj, vector<bool>& mark, long long pos) {
  mark[pos] = true;
  set<long long> ancestors;
  ancestors.insert(pos);
  long long sum = 0;
  while (!mark[adj[pos].first]) {
    mark[adj[pos].first] = true;
    ancestors.insert(adj[pos].first);
    sum += adj[pos].second;
    pos = adj[pos].first;
  }
  sum += adj[pos].second;

  if (ancestors.find(pos) != ancestors.end()) {
    sum -= find_least_cycle(adj, pos);
  }
  return sum;
}

int main() {
  long long n;
  cin >> n;

  vector<pair<long long, long long>> adj(n);
  set<int> unique;
  bool u = true;
  for (long long i = 0; i < n; ++i) {
    pair<long long, long long> v;
    cin >> v.first >> v.second;
    if (unique.find(v.first) != unique.end()) {
      u = false;
    }
    unique.insert(v.first);
    v.first--;
    adj[i] = v;
  }

  vector<bool> mark(n, false);
  set<long long> ancestors;
  long long ans = 0;
  for (long long i = 0; i < n; ++i) {
    if (!mark[i]) {
      if (u) {
        ans += solve2(adj, mark, i);
      } else {
        ans += solve(adj, mark, ancestors, i, 0);
      }
    }
  }

  cout << ans;
}
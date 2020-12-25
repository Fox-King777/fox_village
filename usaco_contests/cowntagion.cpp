#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// remember & sign you stupid!
int dfs(vector<vector<int>>& adjlist, int pos) {
  int num_sick_cows = 1;
  int count = 0;
  while (num_sick_cows < adjlist[pos].size() + 1) {
    count++;
    num_sick_cows *= 2;
  }

  for (int i = 0; i < adjlist[pos].size(); ++i) {
    count += dfs(adjlist, adjlist[pos][i]) + 1;
  }

  return count;
}

int main() {
  int n;
  cin >> n;

  vector<vector<int>> adjlist(n + 1);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    adjlist[a].push_back(b);
  }

  int ans = dfs(adjlist, 1);

  cout << ans;
}
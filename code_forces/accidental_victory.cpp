#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Player {
  long long val;
  int id;
};

bool player_cmp(Player a, Player b) { return a.val < b.val; }

void solve() {
  int n;
  cin >> n;

  vector<Player> list(n);
  for (int i = 0; i < n; ++i) {
    cin >> list[i].val;
    list[i].id = i;
  }
  sort(list.begin(), list.end(), player_cmp);

  vector<long long> presum(n);
  presum[0] = list[0].val;
  for (int i = 1; i < n; ++i) {
    presum[i] = presum[i - 1] + list[i].val;
  }

  set<int> winner;
  for (int i = 0; i < n - 1; ++i) {
    if (presum[i] >= list[i + 1].val) {
      winner.insert(list[i].id);
    } else {
      winner.clear();
    }
  }

  winner.insert(list[n - 1].id);
  cout << winner.size() << endl;
  for (set<int>::iterator it = winner.begin(); it != winner.end(); ++it) {
    cout << *it + 1 << " ";
  }
  cout << endl;
}

int main() {
  int t;
  cin >> t;

  for (int i = 0; i < t; ++i) {
    solve();
  }
}
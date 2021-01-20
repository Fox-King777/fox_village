#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct Measurements {
  int day;
  long long id;
  long long change;
};

bool measurement_cmp(Measurements a, Measurements b) { return a.day < b.day; }

int main() {
  ifstream fin("testdata/milk_measurement/9.in", ifstream::in);

  int n;
  long long g;
  fin >> n >> g;

  map<long long, long long> cows;
  vector<Measurements> m(n);
  map<long long, set<long long>> leaderboard;
  leaderboard.insert(pair<long long, set<long long>>(g, {}));
  for (int i = 0; i < n; ++i) {
    fin >> m[i].day >> m[i].id >> m[i].change;
    if (cows.find(m[i].id) == cows.end()) {
      cows.insert(pair<long long, long long>(m[i].id, g));
      leaderboard[g].insert(m[i].id);
    }
  }
  sort(m.begin(), m.end(), measurement_cmp);

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    set<long long> prev_top(leaderboard.rbegin()->second);

    leaderboard[cows[m[i].id]].erase(m[i].id);
    if (leaderboard[cows[m[i].id]].empty()) {
      leaderboard.erase(cows[m[i].id]);
    }

    cows[m[i].id] += m[i].change;
    if (leaderboard.find(cows[m[i].id]) == leaderboard.end()) {
      leaderboard.insert(pair<long long, set<long long>>(cows[m[i].id], {m[i].id}));
    } else {
      leaderboard[cows[m[i].id]].insert(m[i].id);
    }

    if (prev_top != leaderboard.rbegin()->second) {
      ans++;
    }
  }

  cout << ans;
}
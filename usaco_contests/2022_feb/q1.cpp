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

bool len_cmp(unordered_set<int>& a, unordered_set<int>& b) { return a.size() < b.size(); }

bool check(vector<unordered_set<int>> prefer, int cow, int g) {
  prefer[cow].clear();
  for (int i = 0; i < prefer.size(); ++i) {
    if (prefer[i].find(g) != prefer[i].end()) {
      if (prefer[i].size() == 1) {
        return false;
      }
      prefer[i].erase(g);
    }
  }
  sort(prefer.begin(), prefer.end(), len_cmp);

  int index = 0;
  for (int i = 0; i < prefer.size(); ++i) {
    if (prefer[i].size() == 0) {
      index++;
    }
  }

  for (int i = index; i < prefer.size() - 1; ++i) {
    sort(prefer.begin() + i, prefer.end(), len_cmp);
    auto l = prefer[i].begin();
    int lock = *l;

    for (int j = i + 1; j < prefer.size(); ++j) {
      if (prefer[j].find(lock) != prefer[j].end()) {
        if (prefer[j].size() == 1) {
          return false;
        }
        prefer[j].erase(lock);
      }
    }
  }

  return true;
}

int main() {
  int n;
  cin >> n;

  vector<vector<int>> prefer(n);
  for (int i = 0; i < n; ++i) {
    bool pass = false;
    for (int j = 0; j < n; ++j) {
      int g;
      cin >> g;
      if (!pass) {
        prefer[i].push_back(g);
        if (g == i + 1) {
          pass = true;
        }
      }
    }
  }

  vector<unordered_set<int>> prefer2(n);
  for (int i = 0; i < n; ++i) {
    for (auto& g : prefer[i]) {
      prefer2[i].insert(g);
    }
  }

  vector<int> ans(n);
  for (int i = 0; i < n; ++i) {
    for (auto& g : prefer[i]) {
      if (check(prefer2, i, g)) {
        ans[i] = g;
        break;
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << ans[i] << endl;
  }
}
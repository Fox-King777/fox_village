#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int main() {
  int n, k;
  cin >> n >> k;

  set<int> cycle;
  vector<int> gaps;

  int answer, last = 0;

  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    cycle.insert((a + 11) / 12);
  }

  answer = *cycle.rbegin();

  while (!cycle.empty()) {
    gaps.push_back(*cycle.begin() - last - 1);
    last = *cycle.begin();
    cycle.erase(*cycle.begin());
  }

  sort(gaps.rbegin(), gaps.rend());
  for (int i = 0; i < k - 1 && i < gaps.size(); i++) {
    answer -= gaps[i];
  }
  cout << answer * 12;
}
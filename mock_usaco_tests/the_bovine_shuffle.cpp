#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
  ifstream fin("testdata/the_bovine_shuffle/9.in", ifstream::in);

  int n;
  fin >> n;

  vector<int> adjacency(n);
  vector<int> pointers(n, 0);
  for (int i = 0; i < n; ++i) {
    fin >> adjacency[i];
    adjacency[i]--;
    pointers[adjacency[i]]++;
  }

  int ans = n;
  queue<int> dead;
  for (int i = 0; i < n; ++i) {
    if (pointers[i] == 0) {
      dead.push(i);
      ans--;
    }
  }

  while (!dead.empty()) {
    int v = dead.front();
    dead.pop();
    pointers[adjacency[v]]--;
    if (pointers[adjacency[v]] == 0) {
      dead.push(adjacency[v]);
      ans--;
    }
  }

  cout << ans;
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=764
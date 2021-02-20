#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Path {
  int a, b;
};

int main() {
  ifstream fin("testdata/grass_planting/5.in", ifstream::in);

  int n;
  fin >> n;

  vector<int> arr(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    fin >> a >> b;
    arr[a - 1]++;
    arr[b - 1]++;
  }

  int ans = 0;

  for (int i = 0; i < n; ++i) {
    if (ans < arr[i]) {
      ans = arr[i];
    }
  }

  cout << ans + 1 << endl;
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=894
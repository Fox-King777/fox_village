#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool patience_cmp(int a, int b) { return a > b; }

int main() {
  ifstream fin("testdata/lemonade_line/10.in", ifstream::in);

  int n;
  fin >> n;

  vector<int> cows_patience(n);
  for (int i = 0; i < n; ++i) {
    fin >> cows_patience[i];
  }
  sort(cows_patience.begin(), cows_patience.end(), patience_cmp);

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (cows_patience[i] >= ans) {
      ans++;
    }
  }

  cout << ans;
}
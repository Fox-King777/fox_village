#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main() {
  ifstream fin("testdata/circular_barn/1.in", ifstream::in);

  int n;
  fin >> n;

  int num_c = 0;
  vector<int> barn(n);
  for (int i = 0; i < n; ++i) {
    fin >> barn[i];
    num_c = max(0, num_c + barn[i] - 1);
  }

  for (int i = 0; i < n; ++i) {
    if (num_c == 0) {
      rotate(barn.begin(), barn.begin() + i, barn.begin() + n);
      break;
    }
    num_c = max(0, num_c + barn[i] - 1);
  }

  long long ans = 0;
  queue<int> q;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < barn[i]; ++j) {
      q.push(i);
    }
    int beg = q.front();
    q.pop();
    ans += (i - beg) * (i - beg);
  }

  cout << ans;
}
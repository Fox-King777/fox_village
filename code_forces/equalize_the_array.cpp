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

vector<int> compress(vector<long long>& a) {
  vector<int> compressed;
  compressed.push_back(1);
  int index = 0;
  for (int i = 1; i < a.size(); ++i) {
    if (a[i] != a[i - 1]) {
      compressed.push_back(0);
      index++;
    }
    compressed[index]++;
  }
  sort(compressed.begin(), compressed.end());

  return compressed;
}

int solve(vector<int>& compressed, int c) {
  int sum = 0;
  for (int i = 0; i < compressed.size(); ++i) {
    if (compressed[i] >= c) {
      sum += compressed[i] - c;
    } else {
      sum += compressed[i];
    }
  }

  return sum;
}

int main() {
  int t;
  cin >> t;

  for (int i = 0; i < t; ++i) {
    int n, ans = numeric_limits<int>::max();
    cin >> n;

    vector<long long> a(n);
    for (int j = 0; j < n; ++j) {
      cin >> a[j];
    }
    sort(a.begin(), a.end());
    vector<int> compressed = compress(a);

    set<int> unique;
    for (int e : compressed) {
      unique.insert(e);
    }

    for (set<int>::iterator it = unique.begin(); it != unique.end(); ++it) {
      ans = min(ans, solve(compressed, *it));
    }
    cout << ans << endl;
  }
}
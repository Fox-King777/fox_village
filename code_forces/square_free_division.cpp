#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

void insert_nono_nums(unordered_set<long long>& nono_nums, long long num) {
  for (int i = 1; i <= 3162; ++i) {
    if (pow(i, 2) <= num) {
      nono_nums.insert(num - pow(i, 2));
    } else {
      break;
    }
  }

  for (int i = 1; i <= (int)sqrt(num); ++i) {
    nono_nums.insert(i);
  }
}

void solve() {
  int n, k;
  cin >> n >> k;

  int ans = 1;
  unordered_set<long long> nono_nums;
  for (int i = 0; i < n; ++i) {
    long long num;
    cin >> num;

    if (nono_nums.find(num) == nono_nums.end()) {
      insert_nono_nums(nono_nums, num);
    } else {
      nono_nums.clear();
      insert_nono_nums(nono_nums, num);
      ans++;
    }
  }

  cout << ans << endl;
}

int main() {
  int t;
  cin >> t;

  for (int i = 0; i < t; ++i) {
    solve();
  }
}
#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

bool rest_stop_cmp(pair<int, int> a, pair<int, int> b) { return a.second > b.second; }

int main() {
  ifstream fin("testdata/rest_stops/10.in", ifstream::in);

  long long l, n, rf, rb;
  fin >> l >> n >> rf >> rb;

  vector<pair<int, int>> rest_stops(n);
  for (int i = 0; i < n; ++i) {
    fin >> rest_stops[i].first >> rest_stops[i].second;
  }
  sort(rest_stops.begin(), rest_stops.end(), rest_stop_cmp);

  long long ans = 0;
  long long index = 0;
  for (int i = 0; i < n; ++i) {
    if (index < rest_stops[i].first) {
      ans += (rest_stops[i].first - index) * (rf - rb) * rest_stops[i].second;
      index = rest_stops[i].first;
    }
  }

  cout << ans;
}
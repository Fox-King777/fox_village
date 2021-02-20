#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct Interval {
  long long s, e;
};

struct max_point {
  long long e;
  long long idx;
};

bool inter_cmp(Interval a, Interval b) { return a.s < b.s; }

int main() {
  ifstream fin("testdata/life_guards/10.in", ifstream::in);

  int n;
  fin >> n;

  vector<Interval> cows(n);
  for (int i = 0; i < n; ++i) {
    fin >> cows[i].s >> cows[i].e;
  }
  sort(cows.begin(), cows.end(), inter_cmp);

  vector<long long> effectiveness(n, 0);  // if you fire this cows, how much time do you lose?
  long long time = 0;
  max_point max_endpoint;
  max_endpoint.e = 0;
  for (int i = 0; i < n; ++i) {
    effectiveness[i] = cows[i].e - cows[i].s;

    if (i > 0 && max_endpoint.e > cows[i].s) {
      effectiveness[i] -= (max_endpoint.e - cows[i].s);
      effectiveness[i] = max(effectiveness[i], (long long)0);
      effectiveness[max_endpoint.idx] -= (max_endpoint.e - cows[i].s);
      effectiveness[max_endpoint.idx] = max(effectiveness[max_endpoint.idx], (long long)0);
    }
    time += effectiveness[i];

    if (max_endpoint.e < cows[i].e) {
      max_endpoint.e = cows[i].e;
      max_endpoint.idx = i;
    }
  }
  sort(effectiveness.begin(), effectiveness.end());

  cout << time - effectiveness[0];
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=786
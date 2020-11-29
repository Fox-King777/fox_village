#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Lifeguard {
  int s, e;
};

bool cows_cmp(Lifeguard a, Lifeguard b) {
  if (a.s != b.s) {
    return a.s < b.s;
  } else {
    return a.e > b.e;
  }
}

void remove_supercedes(vector<Lifeguard>& cows) {
  int max_end = numeric_limits<int>::min();
  int num_kept = 0;
  for (auto& in : cows) {
    if (in.e > max_end) {
      cows[num_kept++] = in;
    }
    max_end = max(max_end, in.e);
  }
  cows.resize(num_kept);
}

int main() {
  ifstream fin("testdata/lifeguards/2.in", ifstream::in);
  int n, k;
  fin >> n >> k;

  vector<Lifeguard> cows;
  for (int i = 0; i < n; ++i) {
    Lifeguard input;
    fin >> input.s >> input.e;
    cows.emplace_back(input);
  }

  sort(cows.begin(), cows.end(), cows_cmp);
  remove_supercedes(cows);

  k -= (n - cows.size());
  for (int i = 0; i < cows.size(); ++i) {
    cout << cows[i].s << " " << cows[i].e << endl;
  }
}
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct Measurements {
  int day;
  long long id;
  long long change;
};

bool measurement_cmp(Measurements a, Measurements b) { return a.day < b.day; }

int main() {
  ifstream fin("testdata/milk_measurement/7.in", ifstream::in);

  int n;
  long long g;
  fin >> n >> g;

  map<long long, long long> cows;
  vector<Measurements> m(n);
  set<long long> top;
  for (int i = 0; i < n; ++i) {
    fin >> m[i].day >> m[i].id >> m[i].change;
    cows.insert(pair<long long, long long>(m[i].id, g));
    top.insert(m[i].id);
  }
  sort(m.begin(), m.end(), measurement_cmp);

  int ans = 0;
  long long max = g;
  for (int i = 0; i < n; ++i) {
    long long prev_cow = cows[m[i].id];
    cows[m[i].id] += m[i].change;

    if (cows[m[i].id] > max) {
      ans++;
      max = cows[m[i].id];
      top = {m[i].id};
    } else if (prev_cow < max && cows[m[i].id] == max) {
      ans++;
      top.insert(m[i].id);
    } else if (prev_cow == max && cows[m[i].id] < max) {
      top.erase(m[i].id);
      if (!top.empty()) {
        ans++;
      } else {
        long long new_max = 0;
        for (int j = 0; j < n; ++j) {
          if (cows[m[j].id] > new_max) {
            new_max = cows[m[j].id];
          }
        }

        top.clear();
        for (int j = 0; j < n; ++j) {
          if (cows[m[j].id] == new_max) {
            top.insert(m[j].id);
          }
        }

        if (top.size() > 1) {
          ans++;
        }
        max = new_max;
      }
    }
  }

  cout << ans;
}
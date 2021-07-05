#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct City {
  string city;
  string state;
};

int main() {
  ifstream fin("testdata/cities_and_states/5.in", ifstream::in);

  int n;
  fin >> n;

  map<string, int> map;
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    string city;
    string state;
    fin >> city >> state;
    city = city.substr(0, 2);
    if (city != state) {
      ans += map[state + city];
    }
    map[city + state]++;
  }

  cout << ans << endl;
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=667
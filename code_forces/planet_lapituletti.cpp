#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

bool valid(int h, int m, string t) {
  int hr = 10 * (t[0] - '0') + (t[1] - '0');
  int min = 10 * (t[3] - '0') + (t[4] - '0');
  if (hr >= h || min >= m) {
    return false;
  }

  return true;
}

string mirror(int h, int m, string time) {
  string mir = "";
  for (int i = 4; i >= 0; --i) {
    if (i == 2) {
      mir += ":";
      continue;
    }

    if (time[i] == '0' || time[i] == '1' || time[i] == '8') {
      mir += time[i];
    } else if (time[i] == '2') {
      mir += '5';
    } else if (time[i] == '5') {
      mir += '2';
    } else {
      return "";
    }
  }
  if (!valid(h, m, mir)) {
    return "";
  }

  return mir;
}

void solve() {
  int h, m;
  cin >> h >> m;

  string time;
  cin >> time;

  while (mirror(h, m, time) == "") {
    int hr = 10 * (time[0] - '0') + (time[1] - '0');
    int min = 10 * (time[3] - '0') + (time[4] - '0') + 1;
    hr += min / m;
    min %= m;
    hr %= h;
    time = "";

    if (hr < 10) {
      time += "0" + to_string(hr);
    } else {
      time += to_string(hr);
    }
    time += ":";

    if (min < 10) {
      time += "0" + to_string(min);
    } else {
      time += to_string(min);
    }
  }

  cout << time << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
}
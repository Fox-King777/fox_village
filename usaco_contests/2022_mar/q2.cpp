#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int main() {
  string s, t;
  int Q;
  cin >> s >> t >> Q;

  for (int i = 0; i < Q; ++i) {
    string q;
    cin >> q;

    set<char> restr;
    for (int j = 0; j < q.size(); ++j) {
      restr.insert(q[j]);
    }

    string news, newt;
    for (int j = 0; j < s.size(); ++j) {
      if (restr.find(s[j]) != restr.end()) {
        news.push_back(s[j]);
      }
      if (restr.find(t[j]) != restr.end()) {
        newt.push_back(t[j]);
      }
    }

    if (newt == news) {
      cout << "Y";
    } else {
      cout << "N";
    }
  }
}
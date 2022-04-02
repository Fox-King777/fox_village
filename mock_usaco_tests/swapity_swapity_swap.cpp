#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
  long long n, m, k;
  cin >> n >> m >> k;

  vector<pair<int, int>> reverses;
  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    l--;
    r--;
    reverses.push_back(make_pair(l, r));
  }

  vector<int> rev_list(n);
  for (int i = 0; i < n; ++i) {
    rev_list[i] = i;
  }

  for (int i = 0; i < m; ++i) {
    reverse(rev_list.begin() + reverses[i].first, rev_list.begin() + reverses[i].second + 1);
  }

  vector<vector<int>> cycles;
  vector<bool> mark(n, false);
  for (int i = 0; i < n; ++i) {
    if (!mark[i]) {
      int current = rev_list[i];
      vector<int> c;
      c.push_back(current);
      mark[current] = true;
      while (current != i) {
        current = rev_list[current];
        c.push_back(current);
        mark[current] = true;
      }
      // reverse(c.begin(), c.end());
      cycles.push_back(c);
    }
  }

  vector<int> ans(n);
  for (auto& cycle : cycles) {
    for (int i = 0; i < cycle.size(); ++i) {
      ans[cycle[i]] = cycle[(i + k) % cycle.size()];
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << ans[i] + 1 << endl;
  }
}
/*
62
9
15
43
48
6
86
65
64
10
50
21
18
32
19
92
29
61
3
2
17
97
38
24
53
55
93
4
71
77
52
12
1
23
83
40
70
34
98
78
37
44
94
56
8
30
16
41
75
31
39
91
74
5
60
42
82
95
80
20
59
54
73
28
45
58
76
49
63
46
14
35
69
25
68
99
13
36
81
11
57
7
22
87
72
67
90
88
89
84
47
27
33
79
66
26
96
51
85
100
*/
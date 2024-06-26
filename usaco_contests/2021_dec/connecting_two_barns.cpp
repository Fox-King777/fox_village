#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

void floodfill(vector<int>& connected, vector<vector<int>>& adj, int c, int in) {
  queue<int> q;
  q.push(in);
  connected[in] = c;
  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (auto& n : adj[v]) {
      if (connected[n] == -1) {
        connected[n] = c;
        q.push(n);
      }
    }
  }
}

int main() {
  int t;
  cin >> t;

  for (int s = 0; s < t; ++s) {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
      int a, b;
      cin >> a >> b;
      a--;
      b--;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }

    vector<int> connected(n, -1);
    int c = 0;
    for (int i = 0; i < n; ++i) {
      if (connected[i] == -1) {
        floodfill(connected, adj, c, i);
        c++;
      }
    }  // O(N)

    // corner case
    if (connected[n - 1] == 0) {
      cout << 0 << endl;
      continue;
    }

    int b1;
    vector<long long> b1_cost(c, 10000000000);
    for (int i = 0; i < n; ++i) {
      if (connected[i] == 0) {
        b1 = i;
      }
      b1_cost[connected[i]] = min(b1_cost[connected[i]], (long long)(i - b1) * (long long)(i - b1));
    }

    for (int i = b1; i >= 0; --i) {
      if (connected[i] == 0) {
        b1 = i;
      }
      b1_cost[connected[i]] = min(b1_cost[connected[i]], (long long)(i - b1) * (long long)(i - b1));
    }

    int bn;
    vector<long long> bn_cost(c, 10000000000);
    for (int i = n - 1; i >= 0; --i) {
      if (connected[i] == connected[n - 1]) {
        bn = i;
      }
      bn_cost[connected[i]] = min(bn_cost[connected[i]], (long long)(i - bn) * (long long)(i - bn));
    }

    for (int i = bn; i < n; ++i) {
      if (connected[i] == connected[n - 1]) {
        bn = i;
      }
      bn_cost[connected[i]] = min(bn_cost[connected[i]], (long long)(i - bn) * (long long)(i - bn));
    }

    long long ans = 100000000000;
    for (int i = 0; i < c; ++i) {
      ans = min(ans, b1_cost[i] + bn_cost[i]);
    }

    cout << ans << endl;
  }
}
/*
2
5 2
1 2
4 5
5 3
1 2
2 3
4 5

20
11 15
8 5
11 9
7 2
3 11
3 4
3 1
7 11
6 3
10 9
2 10
8 9
5 10
9 2
5 2
3 5
6 7
1 5
4 5
5 2
6 1
3 5
5 6
3 6
6 12
3 6
3 1
2 1
2 3
4 1
6 1
5 6
4 3
5 1
2 4
2 6
5 3
3 0
8 10
7 8
6 3
7 4
7 2
3 2
4 8
6 1
8 5
6 8
7 1
14 50
13 9
10 3
5 13
3 14
6 9
2 3
14 11
3 8
4 2
14 6
12 4
13 3
5 10
7 5
10 13
11 7
1 9
7 1
14 4
2 1
3 6
12 1
6 8
2 12
10 6
8 1
11 10
7 12
14 12
7 9
14 1
3 11
12 13
3 9
4 9
7 4
11 5
14 10
5 2
5 1
1 4
6 7
14 9
12 9
12 3
13 4
3 5
10 1
13 7
6 13
7 19
1 7
6 5
1 4
4 2
2 3
7 5
3 4
2 1
6 7
1 3
3 7
1 6
7 4
1 5
2 5
6 2
6 3
3 5
4 6
14 68
1 3
1 12
2 14
14 9
9 13
1 13
14 8
9 2
10 5
5 3
4 1
3 11
13 12
7 1
9 12
12 14
8 9
7 2
10 14
7 14
4 3
2 3
6 12
8 5
6 5
10 8
7 3
7 13
10 3
12 10
2 12
10 1
4 12
2 1
2 13
6 2
8 6
12 3
14 13
5 2
12 5
9 6
12 11
7 4
8 2
3 14
13 11
12 7
10 2
13 4
10 13
3 8
4 10
11 8
10 9
1 8
5 13
13 3
13 8
5 14
9 5
14 1
5 4
6 11
8 7
8 4
9 1
2 4
9 21
6 4
9 8
6 7
5 1
2 5
4 3
9 5
1 8
4 9
3 2
6 9
2 7
3 1
3 9
6 3
7 3
9 7
2 8
6 8
5 4
8 3
13 26
3 9
4 6
7 3
9 2
6 8
10 8
10 7
7 8
11 12
4 12
11 9
3 11
10 12
11 5
11 13
2 6
2 12
6 9
5 8
11 2
12 7
11 4
2 5
11 1
5 4
8 9
2 1
2 1
10 7
10 7
8 2
4 1
9 1
3 2
8 9
8 1
9 10
2 9
1 2
4 9
7 3
1 8
1 3
4 1
3 9
7 6
5 1
18 47
15 1
8 16
15 2
4 5
7 8
6 10
9 7
5 1
11 18
16 4
4 1
7 17
2 7
9 11
2 18
18 4
14 7
15 7
3 4
3 17
10 2
7 6
11 16
13 18
2 3
13 17
18 3
17 16
10 13
2 11
12 2
10 9
11 6
9 12
15 6
17 12
10 11
9 16
8 12
15 18
15 4
1 16
2 16
8 9
14 9
14 1
3 8
14 17
3 6
11 4
1 8
2 1
3 2
6 9
3 5
7 11
12 7
6 5
10 2
11 3
13 14
3 9
12 3
2 11
13 6
11 48
5 6
4 2
6 8
1 11
2 7
7 8
7 10
7 11
11 5
10 3
8 1
1 2
11 8
3 1
7 4
6 3
9 5
11 6
7 3
1 7
3 2
5 8
2 5
7 5
9 7
4 10
2 9
2 8
3 9
11 4
5 3
9 6
8 3
4 6
1 6
7 6
10 5
8 9
2 11
11 9
10 6
9 4
11 10
3 11
10 1
10 9
6 2
4 1
13 73
1 9
5 4
4 9
1 10
13 11
9 13
11 7
13 4
3 11
5 1
5 13
11 10
13 7
1 3
8 10
10 13
12 2
7 10
4 6
12 8
8 9
6 3
6 9
10 2
8 5
2 3
2 13
3 7
4 2
7 8
3 13
10 5
6 1
7 4
12 7
8 3
7 2
12 1
6 7
5 7
5 6
12 13
3 5
2 5
8 6
11 9
2 9
8 1
7 1
2 1
11 8
13 8
6 13
5 11
10 12
2 6
1 11
12 4
9 10
10 6
12 6
13 1
5 12
8 4
2 8
3 4
3 10
7 9
12 3
10 4
3 9
4 1
11 4
3 1
1 3
19 56
14 17
15 8
16 15
10 8
13 14
8 3
1 12
5 9
16 18
19 14
9 17
2 3
9 15
3 6
15 1
1 4
7 3
9 1
7 19
4 17
16 13
6 10
4 19
10 18
19 1
9 6
19 5
16 6
7 13
8 16
8 19
5 17
15 14
5 11
18 19
2 5
16 9
4 11
3 14
8 17
17 15
16 5
18 6
18 3
14 9
2 14
17 18
14 1
12 4
5 4
18 7
9 18
17 6
11 18
17 13
5 10
9 22
1 2
3 2
9 3
8 3
7 6
8 2
8 5
8 4
2 4
7 1
7 3
6 5
9 6
2 5
2 7
9 4
3 1
9 5
6 3
8 6
2 6
9 7

*/
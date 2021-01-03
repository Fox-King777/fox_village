#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool pos(vector<int>& t, int wait, int n, int m, int c) {
  int wagons = 1;
  int firstArrival = t[0];
  int firstIndex = 0;
  for (int i = 1; i < n; i++) {
    if (t[i] - firstArrival > wait || i + 1 - firstIndex > c) {
      wagons += 1;
      firstArrival = t[i];
      firstIndex = i;
    }
  }
  return (wagons <= m);
}

int binSearch(vector<int>& t, int n, int m, int c, int low, int high) {
  if (low == high) return low;
  if (low + 1 == high) {
    if (pos(t, low, n, m, c)) {
      return low;
    }
    return high;
  }

  int mid = (low + high) / 2;
  if (pos(t, mid, n, m, c)) {
    return binSearch(t, n, m, c, low, mid);
  } else {
    return binSearch(t, n, m, c, mid + 1, high);
  }
}

int main() {
  ifstream fin("testdata/convention/10.in", ifstream::in);

  int n, m, c;
  fin >> n >> m >> c;

  vector<int> t(n);
  for (int i = 0; i < n; i++) {
    fin >> t[i];
  }

  sort(t.begin(), t.end());
  cout << binSearch(t, n, m, c, 0, 1000000000);
}
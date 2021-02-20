#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ifstream fin("testdata/subsequences_summing_to_seven/4.in", ifstream::in);

  int n;
  fin >> n;

  vector<int> ids(n);

  for (int i = 0; i < n; ++i) {
    fin >> ids[i];
  }

  int answer = 0;
  for (int i = 0; i < n; ++i) {
    long long sum = 0;
    for (int j = i; j < n; ++j) {
      sum += ids[j];
      if (sum % 7 == 0) {
        if (answer < j - i + 1) {
          answer = j - i + 1;
        }
      }
    }
  }

  cout << answer;
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=595
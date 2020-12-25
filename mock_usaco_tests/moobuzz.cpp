#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ifstream fin("testdata/moobuzz/10.in", ifstream::in);

  int n;
  fin >> n;

  int count = 0;
  int ans = 1;
  while (count != n) {
    if (ans % 3 != 0 && ans % 5 != 0) {
      count++;
    }
    ans++;
  }

  cout << ans - 1;
}
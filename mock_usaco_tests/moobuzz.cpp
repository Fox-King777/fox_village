#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

long long calc(long long a) { return a - (a / 3) - (a / 5) + (a / 15); }

int main() {
  ifstream fin("moobuzz.in", ifstream::in);
  ofstream fout("moobuzz.out", ifstream::out);

  long long n;
  fin >> n;

  long long lo = 0;
  long long hi = 1000000000000;
  while (lo <= hi) {
    long long m = lo + (hi - lo) / 2;

    if (calc(m) > n) {
      hi = m - 1;
    }

    if (calc(m) < n) {
      lo = m + 1;
    }

    if (calc(m) == n) {
      while (m % 3 == 0 || m % 5 == 0) {
        m--;
      }
      fout << m;
      break;
    }
  }
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=966
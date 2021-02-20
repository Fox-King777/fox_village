#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ifstream fin("testdata/secret_cow_code/1.in", ifstream::in);

  string code;
  long long n;

  fin >> code >> n;
  long long len = (long long)code.length();
  while (len < n) {
    long long s = len;
    while (s * 2 < n) {
      s *= 2;
    }
    n -= (s + 1);
    if (n == 0) n = s;
  }

  cout << code[n - 1] << endl;
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=692
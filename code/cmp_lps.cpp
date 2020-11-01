#include <iostream>
#include <vector>

using namespace std;

vector<int> cmp_lps(char pat[], int m) {
   vector<int> lps(m);

    int len = 0;
    int i = 1;

    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
              lps[i] = 0;
              i++;
            }
        }
    }
    return lps;
}

int main() {
  int m = 11;
  char pat[m] = {'A', 'A', 'B', 'A', 'A', 'C', 'A', 'A', 'B', 'A', 'A'};
  vector<int> lps = cmp_lps(pat, m); 

  for (int i = 0; i < m; ++i) {
    cout << lps[i] << " ";
  }
}
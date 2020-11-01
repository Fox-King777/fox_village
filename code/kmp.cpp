#include <iostream>
#include <vector>
#include <utility>

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

pair<int, int> kmp(char pat[], char str[], int m, int n) {
    vector<int> lps = cmp_lps(pat, m);

  int i = 0, j = 0; // i length of match, j scanning through str

  while(j < n) {
    if (str[j + 1] == pat[i]) {
        j++;
        i++;
    } else {
        if (i != 0) {
            i = lps[i];
        } else {
          j++;
        }
    }

    if (i == m) {
      return make_pair(j - (i - 1), j);
    }
  }
}

int main() {
    char txt[] = "ABABDABACDABABCABAB"; 
    char pat[] = "ABABCABAB"; 
    pair<int, int> ans = kmp(pat, txt, 9, 19);

    cout << ans.first << " " << ans.second;
}
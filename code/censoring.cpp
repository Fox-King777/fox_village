#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cstring>

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

int kmp(char pat[], char str[], int m, int n) {
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
      return j - (i - 1);
    }
  }

  return -1;
}

int main() { 
    string txt = "whatthemomooofun", w = "moo";
    int n = txt.length(), m = w.length();

    char str[n];
    strcpy(str, txt.c_str());

    char pat[m];
    strcpy(pat, w.c_str());

    while(true) {
      int ans = kmp(pat, str, m, n);
      if (ans == -1) {
        break;
      }
      txt.erase(ans, m);
      strcpy(str, txt.c_str());
      n = txt.length();
    }

    cout << txt;
}
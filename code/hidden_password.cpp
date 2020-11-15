#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

bool cmp(const char* a, const char* b, int length) {
    int k = 0;
    while (k < length) {
        if (a[k] == b[k]) {
          k++;
          continue;
        } else {
          return a[k] < b[k];
        }
    }
    return false;
}


int main() {  
    string str;
    int l;
    cin >> l >> str;

    str += str;

    int i = 0;
    const char* c_str = str.c_str();
    for (int j = 1; i < l; i++) {
      if (cmp(c_str + i, c_str + j, l)) {
        i = j;
      }
    }

    cout << i;
}
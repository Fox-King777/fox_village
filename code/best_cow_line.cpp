#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;

  char str[n];
  for (int i = 0; i < n; ++i) {
    cin >> str[i];
  }

  string ans = "";
  int l = 0, r = n - 1;
  while (l <= r) {
    if (str[l] != str[r]) {
      if (str[l] < str[r]) {
        ans += str[l];
        l++;
      } else {
        ans += str[r];
        r--;
      }
    } else {
      int i = l;
      int j = r;
      while (i <= j && str[i] == str[j]) {
        i++;
        j--;
      }
      if (str[i] < str[j]) {
        ans += str[l];
        l++;
      } else {
        ans += str[r];
        r--;
      }
    }
  }

  cout << ans;
}
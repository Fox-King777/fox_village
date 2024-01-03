#include <bits/stdc++.h>

#include <iostream>

using namespace std;

void print(vector<int>& emails, vector<int>& folders_count, vector<bool>& filed_emails,
           set<int>& window) {
  cout << "email: ";
  for (auto& e : emails) {
    cout << e << " ";
  }
  cout << "\n";

  cout << "folders count: ";
  for (auto& e : folders_count) {
    cout << e << " ";
  }
  cout << "\n";

  cout << "filed emails: ";
  for (bool e : filed_emails) {
    cout << e << " ";
  }
  cout << "\n";

  cout << "window: ";
  for (auto& e : window) {
    cout << e << " ";
  }
  cout << "\n";
}

void solve() {
  int m, n, k;
  cin >> m >> n >> k;

  vector<int> emails(n);
  vector<int> folders_count(m + 1, 0);  // how many emails needs to be filed in each folder
  for (int i = 0; i < n; ++i) {
    cin >> emails[i];
    folders_count[emails[i]]++;
  }

  vector<bool> filed_emails(n, false);  // true if filed, false if not filed
  set<int> window;                      // current folders in window
  for (int i = 1; i <= k; ++i) window.insert(i);

  // scroll forward
  int email_index = 0;
  while (email_index < n) {
    while (folders_count[*window.begin()] == 0 && *window.rbegin() < m) {
      window.insert(*window.rbegin() + 1);
      window.erase(window.begin());
    }

    if (window.find(emails[email_index]) != window.end()) {
      filed_emails[email_index] = true;
      folders_count[emails[email_index]]--;
    }

    email_index++;
  }
  email_index--;

  // print(emails, folders_count, filed_emails, window);
  //   scroll backwards
  while (email_index >= 0) {
    // print(emails, folders_count, filed_emails, window);
    while (folders_count[*window.begin()] == 0 && *window.rbegin() < m) {
      window.insert(*window.rbegin() + 1);
      window.erase(window.begin());
    }

    while (email_index >= 0 && filed_emails[email_index]) {
      email_index--;
    }

    if (email_index < 0) break;

    if (window.find(emails[email_index]) != window.end()) {
      filed_emails[email_index] = true;
      folders_count[emails[email_index]]--;
    } else {
      break;
    }
  }

  // print(emails, folders_count, filed_emails, window);

  for (bool e : filed_emails) {
    if (!e) {
      cout << "NO" << endl;
      return;
    }
  }
  cout << "YES" << endl;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    solve();
  }
}

/*
1
3 10 2
1
3
2
1
3
2
1
3
1
2

1
3 10 1
1
3
2
1
3
2
1
3
2
1

1
5 5 1
1 2 3 5 4
*/
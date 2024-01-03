#include <bits/stdc++.h>

#include <iostream>

using namespace std;

void dec(unordered_map<int, int>& hit_count, int position) {
  if (hit_count.find(position) != hit_count.end()) {
    if (--hit_count[position] == 0) {
      hit_count.erase(position);
    }
  }
}

void inc(unordered_map<int, int>& hit_count, int position, set<int>& unique_targets) {
  if (unique_targets.find(position) != unique_targets.end()) {
    hit_count[position]++;
  }
}

int main() {
  int t, c;
  cin >> t >> c;

  vector<int> targets(t);
  for (int i = 0; i < t; ++i) {
    cin >> targets[i];
  }

  string command;
  cin >> command;

  unordered_map<int, int> hit_count;
  vector<int> pos(command.size(), 0);
  set<int> unique_targets(targets.begin(), targets.end());

  // Forward Scan
  int position = 0;
  for (int i = 0; i < command.size(); ++i) {
    if (command[i] == 'L')
      position -= 1;
    else if (command[i] == 'R')
      position += 1;
    else if (command[i] == 'F')
      inc(hit_count, position, unique_targets);
    pos[i] = position;
  }

  int max_hit = hit_count.size();

  // Replacing L with R
  auto running_count = hit_count;
  for (int i = command.size() - 1; i >= 0; --i) {
    if (command[i] == 'L')
      max_hit = max(max_hit, (int)running_count.size());
    else if (command[i] == 'F') {
      dec(running_count, pos[i]);
      inc(running_count, pos[i] + 2, unique_targets);
    }
  }

  // Replacing L with F
  running_count = hit_count;
  for (int i = command.size() - 1; i >= 0; --i) {
    if (command[i] == 'L') {
      inc(running_count, pos[i], unique_targets);
      max_hit = max(max_hit, (int)running_count.size());
      dec(running_count, pos[i]);
    } else if (command[i] == 'F') {
      dec(running_count, pos[i]);
      inc(running_count, pos[i] + 1, unique_targets);
    }
  }

  // Replacing R with L
  running_count = hit_count;
  for (int i = command.size() - 1; i >= 0; --i) {
    if (command[i] == 'R')
      max_hit = max(max_hit, (int)running_count.size());
    else if (command[i] == 'F') {
      dec(running_count, pos[i]);
      inc(running_count, pos[i] - 2, unique_targets);
    }
  }

  // Replacing R with F
  running_count = hit_count;
  for (int i = command.size() - 1; i >= 0; --i) {
    if (command[i] == 'R') {
      inc(running_count, pos[i], unique_targets);
      max_hit = max(max_hit, (int)running_count.size());
      dec(running_count, pos[i]);
    } else if (command[i] == 'F') {
      dec(running_count, pos[i]);
      inc(running_count, pos[i] + 1, unique_targets);
    }
  }

  // Replacing F with R
  running_count = hit_count;
  for (int i = command.size() - 1; i >= 0; --i) {
    if (command[i] == 'F') {
      dec(running_count, pos[i]);
      max_hit = max(max_hit, (int)running_count.size());
      inc(running_count, pos[i] + 1, unique_targets);
    }
  }

  // Replacing F with L
  running_count = hit_count;
  for (int i = command.size() - 1; i >= 0; --i) {
    if (command[i] == 'F') {
      dec(running_count, pos[i]);
      max_hit = max(max_hit, (int)running_count.size());
      inc(running_count, pos[i] - 1, unique_targets);
    }
  }

  cout << max_hit;
}
/*
3 7
0 -1 1
LFFRFRR

5 6
1 2 3 4 5
FFRFRF

1 5
0
FFFFF
*/
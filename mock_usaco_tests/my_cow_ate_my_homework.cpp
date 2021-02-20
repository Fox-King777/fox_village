#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Problem {
  int idx;
  double average;
};

int main() {
  ifstream fin("testdata/my_cow_ate_my_homework/10.in", ifstream::in);

  int n;
  fin >> n;

  vector<int> questions(n);
  for (int i = n - 1; i >= 0; --i) {
    fin >> questions[i];
  }

  int sum = 0;
  double average = 0;
  double max_average = 0;
  vector<Problem> max_average_idx;
  int minimum = numeric_limits<int>::max();
  for (int i = 0; i < n; ++i) {
    minimum = min(minimum, questions[i]);
    sum += questions[i];

    if (i > 0) {
      average = (sum - minimum) / i;
    }

    if (average >= max_average) {
      max_average = average;
      Problem p;
      p.idx = i + 1;
      p.average = average;
      max_average_idx.push_back(p);
    }
  }

  for (int i = max_average_idx.size() - 1; i >= 0; --i) {
    if (max_average_idx[i].average >= max_average) {
      cout << n - max_average_idx[i].idx << endl;
    }
  }
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=762
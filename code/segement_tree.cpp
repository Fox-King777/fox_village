#include <iostream>
#include <utility>
#include <vector>

using namespace std;

using interval = pair<int, int>;

int len(interval itv) { return itv.second - itv.first; }

string repr(interval itv) {
  char buf[100];
  sprintf(buf, "[%d, %d)", itv.first, itv.second);
  return string(buf);
}

int mid(interval itv) { return (itv.first + itv.second + 1) / 2; }

pair<interval, interval> half(interval itv) { 
    int m = mid(itv);
    return make_pair(interval(itv.first, m), interval(m, itv.second));
}

bool is_disjoint(interval a, interval b) { return a.second <= b.first || b.second <= a.first; }
bool contains(interval a, interval b) { return a.first <= b.first and a.second >= b.second; }

struct Node {
  int data;
  interval itv;
};

void build(vector<Node>& t, int arr[], int i, interval itv) {
    if (len(itv) == 1) {
      t[i].data = arr[itv.first];
    } else if (len(itv) == 0) {
      t[i].data = 0;
    } else {
      auto halfs = half(itv);

      build(t, arr, i * 2 + 1, halfs.first);
      build(t, arr, i * 2 + 2, halfs.second);
      t[i].data = t[i * 2 + 1].data + t[i * 2 + 2].data;
      t[i].itv = itv;
    }
}

int sum(vector<Node>& t, int i, interval qitv) {
    if (contains(qitv, t[i].itv)) {
      return t[i].data;
    } else if (is_disjoint(qitv, t[i].itv)) {
      return 0;
    } else {
      return sum(t, i * 2 + 1, qitv) + sum(t, i * 2 + 2, qitv);
    }
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11};  
    int n = 6;
    vector<Node> t(n * 4);
    for (int i = 0; i < n * 4; i++) {
      t[i].data = 0;
    }

    build(t, arr, 0, interval(0, n));

    for (int i = 0; i < n * 4; i++) {
      cout << t[i].data << " ";
    }
    cout << endl;

    cout << sum(t, 0, interval(1, 4));
}
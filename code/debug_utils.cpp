#include <iostream>

using namespace std;

void print_array(int arr[], int n) {
  for (int i = 0; i < n; ++i) {
    cout << i << ":" << arr[i] << endl;
  }
}

int main() {
  int arr[] = {3, 4, 100, -30, 2};
  print_array(arr, 5);
}
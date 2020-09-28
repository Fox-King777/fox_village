#include <iostream>

using namespace std;

void print_array(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << i << ":" << arr[i] << endl;
    }
}
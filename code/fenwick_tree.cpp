#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

struct FenwickTree
{
    vector<int> partial_sum;

    FenwickTree(int n)
    {
        partial_sum.resize(n, 0);
    }

    int prefix_sum(int k)
    {
        int s = 0;

        while (k >= 0)
        {
            s += partial_sum[k];
            k = this->g(k) - 1;
        }

        return s;
    }

    void add(int k, int val)
    {
        while (k < partial_sum.size())
        {
            partial_sum[k] += val;
            k = this->h(k);
        }
    }

    int g(int i)
    {
        return i & (i + 1);
    }

    int h(int i)
    {
        return i | (i + 1);
    }
};

int main()
{
    auto tree = FenwickTree(10);
    tree.add(0, 3);
    tree.add(1, 5);
    tree.add(2, 2);
    tree.add(3, 3);
    tree.add(4, 10);
    tree.add(5, 14);
    tree.add(6, 7);
    tree.add(7, 9);

    for (int i = 0; i < 8; i++)
    {
        cout << i << " " << tree.prefix_sum(i) << endl;
    }

    cout << endl;
    tree.add(4, -2);
    tree.add(5, 3);

    for (int i = 0; i < 8; i++)
    {
        cout << i << " " << tree.prefix_sum(i) << endl;
    }
}
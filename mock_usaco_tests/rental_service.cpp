#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct Shops {
  long long amount, price;
};

bool shops_cmp(Shops a, Shops b) { return a.price > b.price; }

bool descending_cmps(long long a, long long b) { return a > b; }

int main() {
  ifstream fin("testdata/rental_service/10.in", ifstream::in);

  int n, m, r;
  fin >> n >> m >> r;

  vector<long long> cows(n);
  for (int i = 0; i < n; ++i) {
    fin >> cows[i];
  }
  sort(cows.begin(), cows.end(), descending_cmps);

  vector<Shops> shops(m);
  for (int i = 0; i < m; ++i) {
    fin >> shops[i].amount >> shops[i].price;
  }
  sort(shops.begin(), shops.end(), shops_cmp);

  vector<long long> rentals(r);
  for (int i = 0; i < r; ++i) {
    fin >> rentals[i];
  }
  sort(rentals.begin(), rentals.end(), descending_cmps);

  vector<long long> max_profit(n + 1);
  long long shop_idx = 0;
  for (int i = 0; i < n; ++i) {
    max_profit[i + 1] = max_profit[i];
    while (shop_idx < shops.size() && cows[i] > 0) {
      long long gallons = min(cows[i], shops[shop_idx].amount);
      max_profit[i + 1] += gallons * shops[shop_idx].price;
      cows[i] -= gallons;
      shops[shop_idx].amount -= gallons;
      if (shops[shop_idx].amount == 0) {
        shop_idx++;
      }
    }
  }

  long long c = n - 1;
  long long rental_idx = 0;
  long long rental_profit = 0;
  while (c >= 0 && rental_idx < rentals.size()) {
    rental_profit += rentals[rental_idx];
    max_profit[c] += rental_profit;
    rental_idx++;
    c--;
  }

  long long ans = 0;
  for (int i = 0; i < n + 1; ++i) {
    ans = max(ans, max_profit[i]);
  }

  cout << ans;
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=787
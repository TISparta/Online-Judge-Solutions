// BIT
// 2
// 21-09-2020

#include <bits/stdc++.h>
     
#define all(A) begin(A), end(A)
#define rall(A) rbegin(A), rend(A)
#define sz(A) int(A.size())
#define pb push_back
#define mp make_pair
     
using namespace std;
     
typedef long long ll;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;
typedef vector <int> vi;
typedef vector <ll> vll;
typedef vector <pii> vpii;
typedef vector <pll> vpll;

int main () {
  ios::sync_with_stdio(false); cin.tie(0);
  int n, q;
  cin >> n >> q;
  vll ft(n + 1, 0);
  auto update = [&] (int pos, int val) {
    while (pos < sz(ft)) {
      ft[pos] += val;
      pos += pos & -pos;
    }
  };
  auto sum = [&] (int pos) {
    ll ret = 0;
    while (pos) {
      ret += ft[pos];
      pos -= pos & -pos;
    }
    return ret;
  };
  vi a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    update(i, a[i]);
  }
  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t == 1) {
      update(l, -a[l] + r);
      a[l] = r;
    } else {
      cout << sum(r) -sum(l - 1) << '\n';
    }
  }
  return (0);
}

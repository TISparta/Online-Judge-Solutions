// Suffix Array
// 4
// 31-12-2020

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

struct SuffixArray {
  int n;
  string s;
  vi sa;
  vi lcp;
  const int sigma = 300;

  void counting_sort (int k, const vi& rank) {
    vi cnt(max(sigma, n), 0);
    for (int i = 0; i < n; i++) {
      cnt[(i + k < n) ? rank[i + k] : 0] += 1;
    }
    int sum = 0;
    for (int i = 0; i < sz(cnt); i++) {
      int ci = cnt[i];
      cnt[i] = sum;
      sum += ci;
    }
    vi tmp_sa(n);
    for (int i = 0; i < n; i++) {
      int pos = (sa[i] + k < n) ? rank[sa[i] + k] : 0;
      tmp_sa[cnt[pos]++] = sa[i];
    }
    sa.swap(tmp_sa);
  }

  void construct_SA () {
    sa.resize(n);
    iota(all(sa), 0);
    vi rank(n, 0);
    for (int i = 0; i < n; i++) rank[i] = s[i];
    for (int k = 1; k < n; k <<= 1) {
      counting_sort(k, rank);
      counting_sort(0, rank);
      int r = 0;
      vi tmp_rank(n);
      tmp_rank[sa[0]] = r;
      for (int i = 1; i < n; i++) {
        if (rank[sa[i]] == rank[sa[i - 1]] and
            rank[sa[i] + k] == rank[sa[i - 1] + k]) {
          tmp_rank[sa[i]] = r;
        } else {
          tmp_rank[sa[i]] = ++r;
        }
      }
      rank.swap(tmp_rank);
      if (rank[sa[n - 1]] == n - 1) break;
    }
  }

  pii find (const string& p) {
    pii ret;
    {
      int l = 0, h = n - 1;
      while (l != h) {
        int m = (l + h) >> 1;
        if (s.compare(sa[m], sz(p), p) >= 0) h = m;
        else l = m + 1;
      }
      if (s.compare(sa[l], sz(p), p) != 0) return pii(-1, -2);
      ret.first = l;
    }
    {
      int k = 0;
      while ((1 << k) < n) k += 1;
      int h = ret.first;
      for (int bit = k - 1; bit >= 0; bit--) {
        if (h + (1 << bit) < n and s.compare(sa[h + (1 << bit)], sz(p), p) == 0) {
          h += (1 << bit);
        }
      }
      ret.second = h;
    }
    return ret;
  }

  void construct_LCP () {
    vi rank(n, 0);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    int k = 0;
    lcp.resize(n - 1, 0);
    for (int i = 0; i < n; i++) {
      if (rank[i] == n - 1) { k = 0; continue; }
      int j = sa[rank[i] + 1];
      while (max(i, j) + k < n and s[i + k] == s[j + k]) k += 1;
      lcp[rank[i]] = k;
      k = max(0, k - 1);
    }
  }

  SuffixArray (const string& ss) {
    s = ss;
    s += "$";
    n = sz(s);
    construct_SA();
    construct_LCP();
  }
};


int main () {
  ios::sync_with_stdio(false); cin.tie(0);
  string s, t;
  cin >> s >> t;
  string text = s + "#" + t;
  SuffixArray sa(text);
  int n = sz(s), m = sz(t);
  pii mx(-1, -1);
  for (int i = 0; i < sz(sa.lcp); i++) {
    if (sa.sa[i] < n and sa.sa[i + 1] > n and sa.lcp[i] > mx.first) {
      mx = pii(sa.lcp[i], sa.sa[i]);
    }
    if (sa.sa[i] > n and sa.sa[i + 1] < n and sa.lcp[i] > mx.first) {
      mx = pii(sa.lcp[i], sa.sa[i + 1]);
    }
  }
  cout << s.substr(mx.second, mx.first) << '\n';
  return (0);
}

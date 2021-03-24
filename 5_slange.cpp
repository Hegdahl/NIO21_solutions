#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(0);cin.tie(0);

  int n, m, k; cin >> n >> m >> k;
  vector<ll> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];

  multiset<ll> small, large;

  for (int i = 0; i < m; ++i)
    large.insert(a[i]);

  ll s = 0;

  while ((int)large.size() > k) {
    s += *large.begin();
    small.insert(*large.begin());
    large.erase(large.begin());
  }

  ll ans = s;

  for (int i = 0; i < n-m; ++i) {
    if (small.find(a[i]) != small.end()) {
      small.erase(small.find(a[i]));
      s -= a[i];
    } else {
      large.erase(large.find(a[i]));
    }

    s -= *--small.end();
    large.insert(*--small.end());
    small.erase(--small.end());

    large.insert(a[i+m]);
    while ((int)large.size() > k) {
      s += *large.begin();
      small.insert(*large.begin());
      large.erase(large.begin());
    }
    
    ans = min(ans, s);
  }

  cout << ans << '\n';
  
}

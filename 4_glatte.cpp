#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define ar array

const ll INF = 1LL<<60;

const int mxN = 1000;
ll v[mxN], l[mxN], r[mxN], up[mxN];

// dp[v] = min value when outer=v
map<ll, ll> dp[mxN];

void solve(ll cur) {
  if (l[cur] != -1) solve(l[cur]);
  if (r[cur] != -1) solve(r[cur]);

  if (cur == 0) return;

  auto update = [&](ll outer, ll cost) {
    auto it = dp[cur].find(outer);
    if (it != dp[cur].end()) cost = min(cost, it->second);
    dp[cur][outer] = cost;
  };

  if (l[cur] == -1) {
    update(v[cur], abs(up[cur]-v[cur]));
    return;
  }

  if (r[cur] == -1) {
    for (auto p : dp[l[cur]]) {
      ll outer = p.first;
      ll cost = p.second;

      update(outer, cost + abs(up[cur]-v[cur]));
      update(v[cur], cost + abs(up[cur]-outer));
    }
    return;
  }

  for (auto pl : dp[l[cur]]) {
    ll louter = pl.first;
    ll lcost = pl.second;
    for (auto pr : dp[r[cur]]) {
      ll router = pr.first;
      ll rcost = pr.second;
      ll cost = lcost+rcost;

      update(louter, cost + abs(up[cur]-router));
      update(router, cost + abs(up[cur]-louter));
    }
  }

}

int main() {
  ios::sync_with_stdio(0);cin.tie(0);

  int n; cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> v[i] >> l[i] >> r[i];
    if (l[i] == -1) swap(l[i], r[i]);

    if (l[i] != -1) up[l[i]] = v[i];
    if (r[i] != -1) up[r[i]] = v[i];
  }

  solve(0);

  ll lbest = 0, rbest = 0;

  if (l[0] != -1) {
    lbest = INF;
    for (auto p : dp[l[0]])
      lbest = min(lbest, p.second);
  }
  if (r[0] != -1) {
    rbest = INF;
    for (auto p : dp[r[0]])
      rbest = min(rbest, p.second);
  }

  cout << lbest+rbest << '\n';
}

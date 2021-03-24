#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define ar array

const int mxN = 2500;
vector<ar<ll,2>> g[mxN];

int main() {
  ios::sync_with_stdio(0);cin.tie(0);

  int n, m, k; cin >> n >> m >> k;

  for (int mm = 0; mm < m; ++mm) {
    ll i, j, w; cin >> i >> j >> w;
    g[i].push_back({j, w});
    g[j].push_back({i, w});
    //cerr << i << ' ' << j << ' ' << w << '\n';
  }

  vector<ll> dist(n*(k+1), -1);

  priority_queue<ar<ll, 2>, vector<ar<ll, 2>>, greater<ar<ll, 2>>> pq;
  pq.push({0, 0});

  while (pq.size()) {
    ll dhere = pq.top()[0];
    ll cur = pq.top()[1];

    //cerr << "cur: " << cur << '\n';
    //cerr << "dhere: " << dhere << '\n';

    pq.pop();

    if (cur%n == 1) {
      cout << dhere << '\n';
      return 0;
    }

    if (dist[cur] != -1) continue;
    dist[cur] = dhere;

    ll offs = cur/n*n;
    //cerr << "offs: " << offs << '\n';

    for (auto p : g[cur%n]) {
      ll nxt = p[0];
      ll w = p[1];

      if (dist[nxt+offs] == -1) pq.push({dhere+w, nxt+offs});
      if (nxt+offs+n < n*(k+1) && dist[nxt+offs] == -1) pq.push({dhere, nxt+offs+n});
    }
  }

}

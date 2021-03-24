#include <bits/stdc++.h>

using namespace std;
#define ar array

const int mxN = 2e5;

vector<int> g[mxN];
int minh[mxN], from[mxN];

int dx[256];
int dy[256];

map<ar<int, 2>, int> comp;
vector<ar<int, 2>> compi;

int to_idx(int x, int y) {
  if (!comp.count({x, y})) {
    comp[{x, y}] = compi.size();
    compi.push_back({x, y});
  }
  return comp[{x, y}];
}

ar<int, 2> to_coord(int i) {
  assert(i >= 0);
  assert(i < compi.size());
  return compi[i];
}

int dfs(int i) {
  if (minh[i] == 0) {
    int mx = 0;
    from[i] = -1;
    for (int nxt : g[i]) {
      int cand = dfs(nxt);
      if (cand > mx) {
        from[i] = nxt;
        mx = cand;
      }
    }
    minh[i] = mx+1;
  }

  return minh[i];
}

int main() {
  ios::sync_with_stdio(0);cin.tie(0);

  dx['W'] = -1;
  dx['E'] = 1;
  dy['N'] = -1;
  dy['S'] = 1;

  int n, m, k; cin >> m >> n >> k;

  for (int kk = 0; kk < k; ++kk) {
    int x, y, l; cin >> x >> y >> l;
    string s; cin >> s;

    for (int si = 0; si < l; ++si) {
      int nx = x + dx[s[si]];
      int ny = y + dy[s[si]];
      int i = to_idx(x, y);
      int j = to_idx(nx, ny);
      g[i].push_back(j);
      x = nx;
      y = ny;
    }
  }

  int besti = -1;
  int best = 0;
  for (int i = 0; i < compi.size(); ++i) {
    if (minh[i]==0) dfs(i);
    if (minh[i] > best) {
      best = minh[i];
      besti = i;
    }
  }

  int j = besti;

  while (from[j] != -1) j = from[j];

  //cerr << besti << ' ' << j << ' ' << best << '\n';

  auto p0 = to_coord(besti);
  auto pf = to_coord(j);

  int x0 = p0[0], y0 = p0[1], xf = pf[0], yf = pf[1];

  cout << best-1 << ' ';
  cout << x0 << ' ' << y0 << ' ';
  cout << xf << ' ' << yf << '\n';

}

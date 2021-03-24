#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(0);cin.tie(0);

  int n; cin >> n;
  string s; cin >> s;

  int off_cnt = 0;
  int on_cnt = 1;

  int ans = 0;

  for (int i = 1; i < n; ++i) {
    if (s[i] == s[i-1]) ++on_cnt;
    else {
      off_cnt = on_cnt;
      on_cnt = 1;
    }
    ans = max(ans, min(off_cnt, on_cnt));
  }

  cout << ans << '\n';

}

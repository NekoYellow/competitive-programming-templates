// https://codeforces.com/contest/1931/problem/F
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';

void solve() {
    int n, k;
    cin >> n >> k;

    vector<set<int>> g(n+1);
    vector<bool> vis(n+1), onstack(n+1);

    auto dfs = [&](auto self, int u)->bool {
        vis[u] = 1, onstack[u] = 1;
        for (int v: g[u]) {
            if (vis[v]) {
                if (onstack[v]) return 1;
            } else {
                if (self(self, v)) return 1;
            }
        }
        onstack[u] = 0;
        return 0;
    };

    while (k--) {
        vector<int> a(n);
        for (auto &e: a)
            cin >> e;
        for (int i = 2; i < n; i++) {
            g[a[i-1]].emplace(a[i]);
        }
    }

    bool ok = 1;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        bool cyc = dfs(dfs, i);
        if (cyc) {
            ok = 0;
            break;
        }
    }
    cout << (ok ? "YES" : "NO") << nl;

}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
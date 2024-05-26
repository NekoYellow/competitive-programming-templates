// https://codeforces.com/gym/103931/problem/M
// Using SCC to merge vertices and reduce graph to rag in order to do dfs
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';
#define watch(x) cout << (#x) << ": " << (x) << endl

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<set<int>> G(n), G2(n), g(n);

    while (m--) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
            if (i > 0) {
                G[a[i-1]].emplace(a[i]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (auto v: G[i]) {
            G2[v].emplace(i);
        }
    }

    // START OF SCC (Kosaraju)
    vector<bool> vis(n, 0);
    vector<int> color(n, -1);
    vector<int> s;

    auto dfs1 = [&](auto self, int u)->void {
      vis[u] = true;
      for (int v : G[u])
        if (!vis[v]) self(self, v);
      s.push_back(u);
    };

    auto dfs2 = [&](auto self, int u, int c)->void {
      color[u] = c;
      for (int v : G2[u])
        if (color[v] == -1) self(self, v, c);
    };

    for (int i = 0; i < n; ++i)
        if (!vis[i]) dfs1(dfs1, i);
    int sccCnt = 0;
    for (int i = n-1; i > -1; --i) {
        if (color[s[i]] == -1) {
            dfs2(dfs2, s[i], sccCnt++);
        }
    }
    // END OF SCC

    for (int i = 0; i < n; i++) {
        for (auto v: G[i]) {
            if (color[i] == color[v]) continue;
            g[color[i]].emplace(color[v]);
        }
    }


    map<int, int> colorsz;
    for (int i = 0; i < n; i++) {
        colorsz[color[i]]++;
    }

    vector<int> sz(n, -1);

    auto dfs = [&](auto self, int u)->int {
        if (~sz[u]) return sz[u];
        int res = colorsz[u];
        for (auto v: g[u]) {
            res += self(self, v);
        }
        return sz[u] = res;
    };

    for (int i = 0; i < n; i++) {
        if (sz[color[i]] == -1) dfs(dfs, color[i]);
        cout << sz[color[i]]-1 << ' ';
    }
    cout << nl;

}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
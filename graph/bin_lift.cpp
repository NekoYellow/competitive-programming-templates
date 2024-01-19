// https://www.luogu.com.cn/problem/P3379
#include <bits/stdc++.h>
using namespace std;
const char nl = '\n';
const int B = 31; // for int32_t

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, q, s;
    cin >> n >> q >> s; s--;

    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int u, v;
        cin >> u >> v; u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<vector<int>> anc(n, vector<int>(B, -1));
    vector<int> dep(n);

    auto dfs = [&](auto self, int u, int p)->void {
        anc[u][0] = p;
        dep[u] = ~p ? dep[p]+1 : 0;
        for (int i = 1; i < B; i++) {
            if (anc[u][i-1] == -1) break;
            anc[u][i] = anc[anc[u][i-1]][i-1];
        }
        for (int v: g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
    };

    dfs(dfs, s, -1);

    auto lca = [&](int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        int d = dep[v]-dep[u];
        for (int i = 0; d; i++, d >>= 1) {
            if (d&1) v = anc[v][i];
        }
        if (u == v) return u;
        for (int i = B-1; i > -1; i--) {
            if (anc[u][i] != anc[v][i])
                u = anc[u][i], v = anc[v][i];
        }
        return anc[u][0];
    };

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u-1, v-1)+1 << nl;
    }

    return 0;
}
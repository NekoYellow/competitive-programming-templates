// https://www.luogu.com.cn/problem/U41492 oi-wiki.org/graph/dsu-on-tree
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
vector<int> g[N];
int sz[N], hson[N], lo[N], hi[N], ver[N], ord;
int col[N], cnt[N], totcol, ans[N]; // #colors in subtree

void dfs1(int u, int p) {
    lo[u] = ++ord; ver[ord] = u;
    sz[u] = 1;
    for (auto v: g[u]) {
        if (v == p) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (!hson[u] || sz[v] > sz[hson[u]]) hson[u] = v;
    }
    hi[u] = ord;
}

void dfs2(int u, int p, bool reserve) {
    for (auto v: g[u]) {
        if (v == p || v == hson[u]) continue;
        dfs2(v, u, false);
    }
    if (hson[u]) {
        dfs2(hson[u], u, true);
    }
    for (auto v: g[u]) {
        if (v == p || v == hson[u]) continue;
        for (int i = lo[v]; i <= hi[v]; i++) {
            if (!cnt[col[ver[i]]]++) totcol++;
        }
    }
    if (!cnt[col[u]]++) totcol++;
    ans[u] = totcol;
    if (!reserve) {
        for (int i = lo[u]; i <= hi[u]; i++) {
            if (!--cnt[col[ver[i]]]) totcol--;
        }
    }
}


signed main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> col[i];
    }

    dfs1(1, 0);
    dfs2(1, 0, false);

    int m;
    cin >> m;
    for (; m; m--) {
        int u;
        cin >> u;
        cout << ans[u] << '\n';
    }

    return 0;
}
// https://www.luogu.com.cn/problem/P8436
#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 10; // #edge

int head[N], ver[N*2], nxt[N*2], n, m, tot; // initially set tot = 1
void add(int u, int v) {
    ver[++tot] = v, nxt[tot] = head[u], head[u] = tot;
}

int dfn[N], low[N], ord; bool bridge[N*2];
void tarjan(int u, int in) {
    dfn[u] = low[u] = ++ord;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = ver[i];
        if (!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) bridge[i] = bridge[i^1] = true;
        } else if (i != (in^1)) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
void find_bridge() {
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i, 0);
}

int c[N], bcc;
void dfs(int u) {
    c[u] = bcc;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = ver[i];
        if (c[v] || bridge[i]) continue;
        dfs(v);
    }
}
void find_bcc() {
    for (int i = 1; i <= n; i++)
        if (!c[i]) ++bcc, dfs(i);
}

vector<int> ans[N];

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    tot = 1;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        add(u, v), add(v, u);
    }
    find_bridge(); find_bcc();

    for (int u = 1; u <= n; u++) {
        ans[c[u]].push_back(u);
    }
    cout << bcc << '\n';
    for (int i = 1; i <= bcc; i++) {
        cout << ans[i].size();
        for (auto u: ans[i]) cout << ' ' << u;
        cout << '\n';
    }

    return 0;
}
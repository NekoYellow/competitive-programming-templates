// https://www.luogu.com.cn/problem/P3387
#include <bits/stdc++.h>
using namespace std;

const int N = 2e4 + 10;

int n, m; vector<int> g[N], rg[N];
void add(int u, int v) {
    g[u].push_back(v), rg[v].push_back(u);
}
// Kosaraju
int scc, col[N], stk[N], tp; bool vis[N];
void dfs1(int u) {
    vis[u] = true;
    for (int v : g[u]) if (!vis[v]) dfs1(v);
    stk[++tp] = u;
}
void dfs2(int u, int c) {
    col[u] = c;
    for (int v : rg[u]) if (!col[v]) dfs2(v, c);
}
void find_scc() {
    for (int u = 1; u <= n; ++u) if (!vis[u]) dfs1(u);
    for (; tp; tp--) if (!col[stk[tp]]) dfs2(stk[tp], ++scc);
}


namespace Tarjan {

int dfn[N], low[N], ord, stk[N], tp; bool instack[N];
int scc, col[N], sz[N];

void tarjan(int u) {
    low[u] = dfn[u] = ++ord, stk[++tp] = u, instack[u] = 1;
    for (auto v: g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (instack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        scc++;
        while (stk[tp] != u) {
            col[stk[tp]] = scc;
            sz[scc]++;
            instack[stk[tp--]] = 0;
        }
        col[stk[tp]] = scc;
        sz[scc]++;
        instack[stk[tp--]] = 0;
    }
}


} // namespace Tarjan


int a[N], deg[N], dp[N];

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (; m; m--) {
        int u, v;
        cin >> u >> v;
        add(u, v);
    }
    find_scc();
    
    for (int u = 1; u <= n; u++) {
        a[n + col[u]] += a[u];
        for (auto v: g[u]) {
            if (col[u] == col[v]) continue;
            // g[n + col[u]].push_back(n + col[v]);
            rg[n + col[v]].push_back(n + col[u]);
            deg[n + col[u]]++;
        }
    }

    queue<int> q;
    for (int i = 1; i <= scc; i++) {
        if (!deg[n+i]) q.push(n+i), dp[n+i] = a[n+i];
    }
    while (q.size()) {
        int u = q.front(); q.pop();
        for (auto v: rg[u]) {
            dp[v] = max(dp[v], dp[u] + a[v]);
            if (!(--deg[v])) q.push(v);
        }
    }

    cout << *max_element(dp+n+1, dp+n+scc+1) << '\n';

    return 0;
}
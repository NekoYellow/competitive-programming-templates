// https://www.luogu.com.cn/problem/P3379
#include <bits/stdc++.h>
using namespace std;

class Tarjan { // Answer LCAs Offline. $O(n) + O(q\alpha(q+n)+n)$
  public:
    Tarjan(int _n): n(_n), par(_n), vis(_n) {
        head[0].assign(n, -1); head[1].assign(n, -1);
        iota(par.begin(), par.end(), 0); // init dsu
    }
    void addedge(int u, int v, bool q) { // q=0: add edge; q=1: add query
        edge[q].push_back({v, head[q][u], -1}); head[q][u] = edge[q].size()-1;
        edge[q].push_back({u, head[q][v], -1}); head[q][v] = edge[q].size()-1;
    }
    vector<int> lca(int s) { // offline. answer each query (0-indexed)
        dfs(s);
        vector<int> res;
        for (int i = 0; i < edge[1].size(); i += 2) res.push_back(edge[1][i].lca);
        return res;
    }

  private:
    int n;
    struct Edge { // linked forward repr
        int v, nxt, lca; // to, next edge, lca
    };
    array<vector<Edge>, 2> edge;
    array<vector<int>, 2> head;
    vector<bool> vis;
    vector<int> par; // dsu
    int find(int x) { return (x == par[x] ? x : (par[x] = find(par[x]))); }
    void dfs(int u) { // core
        vis[u] = 1;
        for (int i = head[0][u]; ~i; i = edge[0][i].nxt) {
            Edge& e = edge[0][i];
            if (!vis[e.v]) dfs(e.v), par[e.v] = u;
        }
        for (int i = head[1][u]; ~i; i = edge[1][i].nxt) {
            Edge& e = edge[1][i];
            if (vis[e.v]) edge[1][i^1].lca = e.lca = find(e.v);
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, q, s;
    cin >> n >> q >> s; s--;
    Tarjan lca(n);
    while (--n) {
        int u, v;
        cin >> u >> v;
        lca.addedge(u-1, v-1, 0);
    }
    while (q--) {
        int u, v;
        cin >> u >> v;
        lca.addedge(u-1, v-1, 1);
    }
    for (auto e: lca.lca(s)) cout << e+1 << '\n';

    return 0;
}


namespace Alter {

class BinMul { // Answer LCAs Online. $O(n\log n) + O(q\log n)$
  public:
    BinMul(int _n): n(_n), g(_n), dep(_n) {
        array<int, B> a; a.fill(-1);
        anc.assign(n, a);
    }
    void addedge(int u, int v) { g[u].push_back(v); g[v].push_back(u); }
    void prep(int s) { dfs(s, -1); } // preprocessing
    int lca(int u, int v) { // online. answer one query (0-indexed)
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
    }

  private:
    static const int B = 31; // int32
    int n;
    vector<vector<int>> g; // graph
    vector<array<int, B>> anc; // ancestor (jump table)
    vector<int> dep;
    void dfs(int u, int p) { // prep
        anc[u][0] = p; dep[u] = dep[p]+1;
        for (int i = 1; i < B; i++) {
            if (anc[u][i-1] == -1) break;
            anc[u][i] = anc[anc[u][i-1]][i-1];
        }
        for (int v: g[u])
            if (v != p) dfs(v, u);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, q, s;
    cin >> n >> q >> s; s--;
    BinMul lca(n);
    while (--n) {
        int u, v;
        cin >> u >> v;
        lca.addedge(u-1, v-1);
    }
    lca.prep(s);
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca.lca(u-1, v-1)+1 << '\n';
    }

    return 0;
}

}

// https://www.luogu.com.cn/problem/P4782
#include <bits/stdc++.h>
using namespace std;
const char nl = '\n';

struct SCC { // Kosaraju
  public:
    SCC(int _n) : n(_n), vis(_n), g(_n), rg(_n) { color.assign(_n, -1); }
    void addedge(int from, int to) {
        g[from].push_back(to), rg[to].push_back(from);
    }
    vector<int> getscc() { // return color assignment
        for (int i = 0; i < n; ++i)
            if (!vis[i]) dfs1(i);
        int sccCnt = 0;
        for (int i = n-1; i > -1; --i) {
            if (color[s[i]] == -1) dfs2(s[i], sccCnt++);
        }
        return color;
    }
  private:
    int n;
    vector<bool> vis;
    vector<int> color, s;
    vector<vector<int>> g, rg;
    void dfs1(int u) {
        vis[u] = true;
        for (int v : g[u]) if (!vis[v]) dfs1(v);
        s.push_back(u);
    }
    void dfs2(int u, int c) {
        color[u] = c;
        for (int v : rg[u]) if (color[v] == -1) dfs2(v, c);
    }
};

struct TwoSat {
    int n;
    SCC scc;
    vector<bool> ans;
    TwoSat(int n) : n(n), ans(n), scc(2 * n) {}
    // constraints &&= (b[i] == f) or (b[j] == g)
    void add_clause(int i, bool f, int j, bool g) {
        scc.addedge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
        scc.addedge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
    }
    bool satisfiable() {
        auto id = scc.getscc();
        for (int i = 0; i < n; i++) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            ans[i] = id[2 * i] < id[2 * i + 1];
        }
        return true;
    }
};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int n, m;
    cin >> n >> m;

    TwoSat sat(n);
    while (m--) {
        int i, a, j ,b;
        cin >> i >> a >> j >> b;
        sat.add_clause(i-1, a, j-1, b);
    }

    if (!sat.satisfiable()) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << "POSSIBLE\n";
        for (int e: sat.ans)
            cout << e << ' ';
        cout << nl;
    }

    return 0;
}
// https://codeforces.com/gym/103931/problem/M
// Using SCC to merge vertices and reduce graph to rag in order to do dfs
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';
#define watch(x) cout << (#x) << ": " << (x) << endl

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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<set<int>> G(n), g(n);
    SCC scc(n);

    while (m--) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
            if (i > 0) {
                G[a[i-1]].emplace(a[i]);
                scc.addedge(a[i-1], a[i]);
            }
        }
    }

    auto&& color = scc.getscc();

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
// https://www.luogu.com.cn/problem/P3388
#include <bits/stdc++.h>
using namespace std;

class Tarjan { // 0-indexed
    int n;
    vector<vector<int>> g;
    vector<int> dfn, low;
    vector<bool> vis, cut;
    void dfs(int u, int p, int& ord) {
        vis[u] = 1;
        low[u] = dfn[u] = ord++;
        int ch = 0;
        for (auto v: g[u]) {
            if (!vis[v]) {
                ch++;
                dfs(v, u, ord);
                low[u] = min(low[u], low[v]);
                if (u != p && low[v] >= dfn[u]) {
                    cut[u] = 1;
                }
            } else if (v != p) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (u == p && ch >= 2) {
            cut[u] = 1;
        }
    }
public:
    Tarjan(int _n) :
        n(_n), g(_n),
        dfn(_n), low(_n),
        vis(_n), cut(_n) {}
    void addedge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> cut_vertices() {
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                int ord = 0;
                dfs(i, i, ord);
            }
        }
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (cut[i]) ans.push_back(i);
        }
        return ans;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    Tarjan tj(n);
    for (; m; m--) {
        int u, v;
        cin >> u >> v;
        tj.addedge(u-1, v-1);
    }
    auto &&ans = tj.cut_vertices();
    cout << ans.size() << endl;
    for (auto u: ans)
        cout << u+1 << ' ';
    cout << endl;

    return 0;
}
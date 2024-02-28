// https://codeforces.com/contest/1927/problem/F
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';

struct DSU {
    vector<int> par, nv;
    DSU(int n) {
        par.resize(n); iota(par.begin(), par.end(), 0);
        nv.assign(n, 1);
    }
    int find(int x) {
        if (x == par[x]) return x;
        par[x] = find(par[x]);
        return par[x];
    }
    bool merge(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) {
            return false;
        }
        if (nv[rx] < nv[ry]) {
            par[rx] = ry;
            nv[ry] += nv[rx];
        } else {
            par[ry] = rx;
            nv[rx] += nv[ry];
        }
        return true;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> edges(m);
    for (auto &e: edges) {
        int u, v, w;
        cin >> u >> v >> w;
        e = {w, u-1, v-1};
    }
    sort(edges.begin(), edges.end(), greater());
    
    DSU uf(n);
    vector<vector<int>> adj(n);
    int ans = 1e9;
    int U, V;
    for (auto [w, u, v]: edges) {
        if (!uf.merge(u, v)) {
            U = u, V = v;
            ans = w;
        } else {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    vector<int> path;
    auto dfs = [&](auto self, int u, int p)->bool {
        if (u == V) {
            path.push_back(u);
            return true;
        }
        for (auto v: adj[u]) {
            if (v == p) continue;
            if (self(self, v, u)) {
                path.push_back(u);
                return true;
            }
        }
        return false;
    };
    dfs(dfs, U, V);
    // queue<int> q;
    // map<int, int> prev;
    // q.push(U);
    // prev[U] = V;
    // while (q.size()) {
    //     int u = q.front(); q.pop();
    //     for (auto v: adj[u]) {
    //         if (v == prev[u]) continue;
    //         if (v == V) {
    //             for (int i = u; i != V; i = prev[i])
    //                 path.push_back(i);
    //             path.push_back(v);
    //             while (q.size()) q.pop();
    //             break;
    //         }
    //         q.push(v);
    //         prev[v] = u;
    //     }
    // }

    cout << ans << ' ' << path.size() << nl;
    for (int i: path) cout << i+1 << ' ';
    cout << nl;

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
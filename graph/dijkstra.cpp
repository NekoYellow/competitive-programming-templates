// https://www.luogu.com.cn/problem/P4779
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 1e18;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int n, m, s;
    cin >> n >> m >> s; s--;

    vector<vector<pair<int, int>>> g(n);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w; u--, v--;
        g[u].push_back({v, w});
    }

    vector<ll> dist(n, inf); dist[s] = 0;
    vector<bool> vis(n, 0);
    multiset<pair<ll, int>> pq; pq.emplace(make_pair(0, s));

    while (pq.size()) {
        auto [d, u] = *pq.begin(); pq.extract(pq.begin());
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w]: g[u]) {
            if (vis[v]) continue;
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.emplace(make_pair(dist[v], v));
            }
        }
    }

    for (auto e: dist) cout << e << ' ';
    cout << '\n';

    return 0;
}
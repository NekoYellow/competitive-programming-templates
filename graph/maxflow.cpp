/* Luogu P3376 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';

class MF {
public:
    MF(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        head.resize(n);
        fill(head.begin(), head.end(), -1);
        dep.resize(n);
    }

    void addedge(int u, int v, int w) {
        e.push_back({v, head[u], w, 0});
        head[u] = e.size()-1;
        e.push_back({u, head[v], 0, 0});
        head[v] = e.size()-1;
    }

    ll dinic() {
        ll maxflow = 0;
        int inf = (1 << 31) - 1;
        while (bfs()) {
            cur = head;
            maxflow += dfs(s, inf);
        }
        return maxflow;
    }

private:
    int n; // |V|
    int s, t; // source, sink
    struct Edge {
        int v, nxt, c, f; // to, next edge, capacity, flow
    };
    vector<Edge> e;
    vector<int> head; // forward star repr
    vector<int> dep, cur; // for dfs

    bool bfs() {
        queue<int> q;
        fill(dep.begin(), dep.end(), 0);
        dep[s] = 1;
        q.push(s);
        while (q.size()) {
            int u = q.front(); q.pop();
            for (int i = head[u]; ~i; i = e[i].nxt) {
                int v = e[i].v;
                if (!dep[v] && e[i].c > e[i].f) {
                    dep[v] = dep[u]+1;
                    q.push(v);
                }
            }
        }
        return dep[t]; // if t is reachable from s
    }

    int dfs(int u, int flow) {
        if (u == t || !flow) return flow;
        int ret = 0;
        for (int &i = cur[u]; ~i; i = e[i].nxt) {
            int v = e[i].v;
            if (dep[v] == dep[u]+1) {
                int d = dfs(v, min(flow-ret, e[i].c-e[i].f));
                if (!d) continue;
                e[i].f += d, e[i^1].f -= d;
                ret += d;
                if (ret == flow) break;
            }
        }
        return ret;
    }
};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    MF mf(n, s-1, t-1);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        mf.addedge(u-1, v-1, w);
    }
    cout << mf.dinic() << nl;

    return 0;
}
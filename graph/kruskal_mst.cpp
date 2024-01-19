// https://www.luogu.com.cn/problem/P3366
#include <bits/stdc++.h>
using namespace std;
const char nl = '\n';

struct edge { // undirected
    int u, v;
    int w;
    edge(int _u, int _v, int _w): u(_u), v(_v), w(_w) {}
};
bool operator<(const edge& u, const edge& v) {
    return u.w > v.w;
}

/* heap of edges (with the shortest edge on the top) */
priority_queue<edge> pq;

/* dsu */
vector<int> par, nv;
int nset;
void init(int n) {
    par.resize(n); nv.resize(n);
    iota(par.begin(), par.end(), 0); // let r[i] = i forall i
    fill(nv.begin(), nv.end(), 1);
    nset = n;
}
int find(int x) {
    if (x == par[x]) return x;
    par[x] = find(par[x]);
    return par[x];
}
bool unio(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx != ry) {
        if (nv[rx] < nv[ry]) {
            par[rx] = ry;
            nv[ry] += nv[rx];
        } else {
            par[ry] = rx;
            nv[rx] += nv[ry];
        }
        nset--;
        return true;
    }
    return false;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    init(n);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        pq.push({u, v, w});
        unio(u, v);
    }
    // judge if the graph is connected
    if (nset > 1) {
        cout << "orz" << nl;
        return 0;
    }
    // compute mst
    init(n);
    int tot = 0;
    while (nset > 1) {
        auto [u, v, w] = pq.top();
        pq.pop();
        if (unio(u, v)) {
            tot += w;
        }
    }
    cout << tot << nl;

    return 0;
}

// https://loj.ac/p/10138
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';

const int N = 3e4 + 3, inf = 2e9;

int n, w[N];

// Heavy-path Decomposition.
// Decompose tree to non-overlapping chains (paths)
// Vertices on a chain have continuous dfn, enabling range ops

int fa[N]; vector<int> ch[N];
int sz[N], hson[N], top[N], dfn[N], dep[N], val[N], ord;

void dfs1(int u) {
    sz[u] = 1;
    for (auto v: ch[u]) {
        dep[v] = dep[u] + 1;
        dfs1(v);
        sz[u] += sz[v];
        if (sz[v] > sz[hson[u]]) hson[u] = v;
    }
}

void dfs2(int u, int tp) {
    dfn[u] = ++ord;
    top[u] = tp;
    val[dfn[u]] = w[u]; // value to maintain
    if (hson[u]) dfs2(hson[u], tp);
    for (auto v: ch[u]) {
        if (v != hson[u]) dfs2(v, v);
    }
}


// segment tree

#define le(k) k << 1
#define ri(k) k << 1 | 1
int tr[2][N<<2];
int sm(int x, int y) { return x + y; }
int mx(int x, int y) { return max(x, y); }
function<int(int, int)> op[2] = {sm, mx};

void pushup(int k) {
    for (int i = 0; i < 2; i++)
        tr[i][k] = op[i](tr[i][le(k)], tr[i][ri(k)]);
}

void build(int *src, int k, int L, int R) {
    if (L == R) {
        tr[0][k] = tr[1][k] = src[L];
        return;
    }
    int mid = (L + R) >> 1;
    build(src, le(k), L, mid); build(src, ri(k), mid+1, R);
    pushup(k);
}

void update(int i, int v, int k, int L, int R) {
    if (L == R) {
        tr[0][k] = tr[1][k] = v;
        return;
    }
    int mid = (L + R) >> 1;
    if (i <= mid) update(i, v, le(k), L, mid);
    else update(i, v, ri(k), mid+1, R);
    pushup(k);
}

int query(int type, int l, int r, int k, int L, int R) {
    if (l == L && r == R) {
        return tr[type][k];
    }
    int mid = (L + R) >> 1;
    if (r <= mid) return query(type, l, r, le(k), L, mid);
    if (l > mid) return query(type, l, r, ri(k), mid+1, R);
    return op[type](query(type, l, mid, le(k), L, mid),
                    query(type, mid+1, r, ri(k), mid+1, R));
}


int query(int type, int u, int v) {
    int res = (type ? -inf : 0);
    int fu = top[u], fv = top[v];
    while (fu != fv) {
        if (dep[fu] >= dep[fv])
            res = op[type](res, query(type, dfn[fu], dfn[u], 1, 1, n)), u = fa[fu];
        else
            res = op[type](res, query(type, dfn[fv], dfn[v], 1, 1, n)), v = fa[fv];
        fu = top[u], fv = top[v];
    }
    res = op[type](res, query(type, min(dfn[u], dfn[v]), max(dfn[u], dfn[v]), 1, 1, n));
    return res;
}


vector<int> g[N];

void treedfs(int u, int p) { // make the tree rooted
    for (auto v: g[u]) {
        if (v == p) continue;
        fa[v] = u; ch[u].push_back(v);
        treedfs(v, u);
    }
}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    treedfs(1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    dfs1(1); dfs2(1, 1);

    build(val, 1, 1, n);

    int q;
    cin >> q;
    for (; q; q--) {
        string type; int u, v;
        cin >> type >> u >> v;
        if (type[0] == 'Q') {
            int t = (type == "QMAX");
            cout << query(t, u, v) << '\n';
        } else {
            update(dfn[u], v, 1, 1, n);
        }
    }

    return 0;
}

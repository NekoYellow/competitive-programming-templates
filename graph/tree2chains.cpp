// https://ac.nowcoder.com/acm/contest/81600/G
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';

const int N = 2e5 + 3, M = 998244353;

int inv[N];

// tree chain-decomposition
// Decompose tree to non-overlapping chains.
// Vertices on a chain have continuous dfn, enabling range ops.

int fa[N]; vector<int> ch[N];
int sz[N], hson[N], top[N], val[N], dfn[N], cnt;

void dfs1(int u) {
    sz[u] = 1;
    for (auto v: ch[u]) {
        dfs1(v);
        sz[u] += sz[v];
        if (sz[v] > sz[hson[u]]) hson[u] = v;
    }
}

void dfs2(int u, int tp) {
    dfn[u] = ++cnt;
    top[u] = tp;
    if (hson[u]) {
        val[dfn[u]] = 1ll * sz[hson[u]] * inv[sz[u]] % M; // value to maintain
        dfs2(hson[u], tp);
    }
    for (auto v: ch[u]) {
        if (v != hson[u]) dfs2(v, v);
    }
}

// segment tree (single & range assignment)

int mem[N<<2], tr[N<<2]; bitset<(N<<2)> tag;

#define op(x, y) 1ll * x * y % M
#define le(k) k << 1
#define ri(k) k << 1 | 1

void load(int k) {
    tr[k] = mem[k], tag[k] = 1;
}

void pushdown(int k) {
    if (!tag[k]) return;
    load(le(k)), load(ri(k));
    tag[k] = 0;
}

void build(int *src, int k, int L, int R) {
    if (L == R) {
        mem[k] = src[L];
        return;
    }
    int mid = (L + R) >> 1;
    build(src, le(k), L, mid);
    build(src, ri(k), mid+1, R);
    mem[k] = op(mem[le(k)], mem[ri(k)]);
}

void update(int i, int v, int k, int L, int R) {
    if (L == R) {
        tr[k] = v;
        return;
    }
    pushdown(k);
    int mid = (L + R) >> 1;
    if (i <= mid) update(i, v, le(k), L, mid);
    else update(i, v, ri(k), mid+1, R);
    tr[k] = op(tr[le(k)], tr[ri(k)]);
}

void rload(int l, int r, int k, int L, int R) { // range load
    if (l == L && r == R) {
        load(k);
        return;
    }
    pushdown(k);
    int mid = (L + R) >> 1;
    if (r <= mid) rload(l, r, le(k), L, mid);
    else if (l > mid) rload(l, r, ri(k), mid+1, R);
    else rload(l, mid, le(k), L, mid), rload(mid+1, r, ri(k), mid+1, R);
    tr[k] = op(tr[le(k)], tr[ri(k)]);
}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, q;
    cin >> n >> q;

    for (int i = 2; i <= n; i++) {
        cin >> fa[i];
        ch[fa[i]].push_back(i);
    }

    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = 1ll * (M - M / i) * inv[M % i] % M;
    }
    int nfac = 1;
    for (int i = 1; i <= n; i++) {
        nfac = 1ll * nfac * i % M;
    }

    dfs1(1); dfs2(1, 1);

    build(val, 1, 1, n); // use sz(hson(u))/sz(u) to build tree on mem

    for (int u = 1; u <= n; u++) {
        update(dfn[u], inv[sz[u]], 1, 1, n); // assign to 1/sz(u) first
    }

    for (int _ = 0; _ < q; _++) {
        int u;    // access(u): set the upwards edges (real) after resetting
        cin >> u; // all downwards edges (virtual) on the chain root -> u

        update(dfn[u], inv[sz[u]], 1, 1, n); // bottom of chain
        for (; ; ) {
            if (u != top[u]) {
                // assign vertices on chain back to sz(hson(u))/sz(u)
                rload(dfn[top[u]], dfn[fa[u]], 1, 1, n);
                u = top[u];
            }
            if (u == 1) break;
            // across chain
            update(dfn[fa[u]], 1ll * sz[u] * inv[sz[fa[u]]] % M, 1, 1, n);
            u = fa[u];
        }
        // query #perm(n) giving the current tree state. the equation is
        // n! x (sz(v)/sz(u) for real edges u->v) x (1/sz(u) for other u's)
        cout << 1ll * tr[1] * nfac % M << nl;
    }

    return 0;
}
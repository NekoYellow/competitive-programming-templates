// https://www.luogu.com.cn/problem/P3384
// alter: https://loj.ac/p/10138
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<class T>
class SegTree { // 1-indexed
  public:
    // op(f(y)(x1), ..., f(y)(xn)) = f(pow(y, n))(op(x1, ..., xn))
    const T e; // op(x, e) = x
    const function<T(T, T)> op; // for query
    const function<T(T, int)> pow;
    const T id; // f(x, id) does nothing
    const function<void(T&, T)> f; // for update

    SegTree(int _n, T _e, function<T(T, T)> _op, function<T(T, int)> _pow, T _id, function<void(T&, T)> _f)
    : n(_n), e(_e), op(_op), pow(_pow), id(_id), f(_f) {
        t.assign((n+1) << 2, e); tag.assign((n+1) << 2, id);
    }

    void update(int l, int r, T val) {
        return update(l, r, val, 1, 1, n);
    }

    T query(int l, int r) {
        return query(l, r, 1, 1, n);
    }

  private:
    int n;
    vector<T> t, tag;

    void pushdown(int k, int L, int R) {
        if (tag[k] == id) return;
        int M = (L + R) >> 1;
        f(t[k << 1], pow(tag[k], M-L+1));
        f(tag[k << 1], tag[k]);
        f(t[k << 1 | 1], pow(tag[k], R-M));
        f(tag[k << 1 | 1], tag[k]);
        tag[k] = id;
    }

    void update(int l, int r, T val, int k, int L, int R) {
        if (l == L && r == R) {
            int len = r-l+1;
            f(t[k], pow(val, len));
            f(tag[k], val);
            return;
        }
        pushdown(k, L, R);
        int M = (L + R) >> 1;
        if (r <= M) update(l, r, val, k << 1, L, M);
        else if (l > M) update(l, r, val, k << 1 | 1, M+1, R);
        else update(l, M, val, k << 1, L, M),
             update(M+1, r, val, k << 1 | 1, M+1, R);
        t[k] = op(t[k << 1], t[k << 1 | 1]);
    }

    T query(int l, int r, int k, int L, int R) {
        if (l == L && r == R) return t[k];
        pushdown(k, L, R);
        int M = (L + R) >> 1;
        if (r <= M) return query(l, r, k << 1, L, M);
        if (l > M) return query(l, r, k << 1 | 1, M+1, R);
        return op(query(l, M, k << 1, L, M),
                  query(M+1, r, k << 1 | 1, M+1, R));
    }
};

// Heavy-path Decomposition.
// Decompose tree to non-overlapping chains (paths)
// Vertices on a chain have continuous dfn, enabling range ops

template <class T>
class HPD { // 1-indexed
  public:
    HPD(int _n, int _r, SegTree<T> _sgt):
        n(_n), root(_r), sgt(_sgt), e(_sgt.e), op(_sgt.op),
        g(_n+1), par(_n+1), hson(_n+1), sz(_n+1),
        dep(_n+1), top(_n+1), dfn(_n+1) {}
    void addedge(int u, int v) { // before init
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void init() {
        tree_build(root);
        ord = 0;
        tree_decompose(root, root);
    }
    void update(int u, int v, T x) { // after init
        for (int fu = top[u], fv = top[v]; fu != fv; fu = top[u], fv = top[v]) {
            if (dep[fu] >= dep[fv])
                sgt.update(dfn[fu], dfn[u], x), u = par[fu];
            else
                sgt.update(dfn[fv], dfn[v], x), v = par[fv];
        }
        sgt.update(min(dfn[u], dfn[v]), max(dfn[u], dfn[v]), x);
    }
    void update(int u, T x) {
        sgt.update(dfn[u], dfn[u]+sz[u]-1, x);
    }
    T query(int u, int v) {
        T res = e;
        for (int fu = top[u], fv = top[v]; fu != fv; fu = top[u], fv = top[v]) {
            if (dep[fu] >= dep[fv])
                res = op(res, sgt.query(dfn[fu], dfn[u])), u = par[fu];
            else
                res = op(res, sgt.query(dfn[fv], dfn[v])), v = par[fv];
        }
        res = op(res, sgt.query(min(dfn[u], dfn[v]), max(dfn[u], dfn[v])));
        return res;
    }
    T query(int u) {
        return sgt.query(dfn[u], dfn[u]+sz[u]-1);
    }

  private:
    const T e;
    const function<T(T, T)> op;
    int n, root, ord;
    vector<vector<int>> g;
    vector<int> par, hson, sz, dep;
    vector<int> top, dfn;
    SegTree<T> sgt;

    void tree_build(int u) {
        sz[u] = 1;
        for (auto v: g[u]) {
            if (v == par[u]) continue;
            par[v] = u;
            dep[v] = dep[u] + 1;
            tree_build(v);
            sz[u] += sz[v];
            if (sz[v] > sz[hson[u]]) hson[u] = v;
        }
    }
    void tree_decompose(int u, int tp) {
        top[u] = tp;
        dfn[u] = ++ord;
        if (hson[u]) tree_decompose(hson[u], tp);
        for (auto v: g[u]) {
            if (v == par[u] || v == hson[u]) continue;
            tree_decompose(v, v);
        }
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, r, p;
    cin >> n >> m >> r >> p;
    vector<ll> val(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
        val[i] %= p;
    }

    auto add = [&](ll x, ll y) {
        ll sum = x + y;
        if (sum >= p) sum -= p;
        return sum;
    };
    auto mul = [&](ll x, int y) {
        return x*y % p;
    };
    auto add2 = [&](ll &x, ll y) {
        x += y;
        if (x >= p) x -= p;
    };
    SegTree<ll> sgt(n, 0, add, mul, 0, add2);
    HPD hpd(n, r, sgt);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        hpd.addedge(u, v);
    }
    hpd.init();

    for (int i = 1; i <= n; i++) {
        hpd.update(i, i, val[i]);
    }

    for (; m; m--) {
        int type; cin >> type;
        int u, v, x;
        if (type == 1) {
            cin >> u >> v >> x; x %= p;
            hpd.update(u, v, x);
        } else if (type == 2) {
            cin >> u >> v;
            cout << hpd.query(u, v) << '\n';
        } else if (type == 3) {
            cin >> u >> x; x %= p;
            hpd.update(u, x);
        } else {
            cin >> u;
            cout << hpd.query(u) << '\n';
        }
    }

    return 0;
}

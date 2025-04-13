// https://www.luogu.com.cn/problem/P3372
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';

template<class T>
class SegTree {
    int n;
    vector<T> t, tag;
    /* TO FILL IN : op(f(x), f(y)) = f(op(x, y)) */
    const T e = 0; // op(x, e) = x
    inline T op(T x, T y) { return max(x, y); }
    const T id = 0; // f(x, id) does nothing
    inline void f(T &x, T p) { x += p; }

    void pushdown(int k) {
        if (tag[k] == id) return;
        f(t[k << 1], tag[k]), f(tag[k << 1], tag[k]);
        f(t[k << 1 | 1], tag[k]), f(tag[k << 1 | 1], tag[k]);
        tag[k] = id;
    }
    void update(int l, int r, T val, int k, int L, int R) {
        if (l == L && r == R) {
            f(t[k], val); f(tag[k], val); return;
        }
        pushdown(k);
        int M = (L + R) >> 1;
        if (r <= M) update(l, r, val, k << 1, L, M);
        else if (l > M) update(l, r, val, k << 1 | 1, M+1, R);
        else update(l, M, val, k << 1, L, M),
             update(M+1, r, val, k << 1 | 1, M+1, R);
        t[k] = op(t[k << 1], t[k << 1 | 1]);
    }
    T query(int l, int r, int k, int L, int R) {
        if (l == L && r == R) return t[k];
        pushdown(k);
        int M = (L + R) >> 1;
        if (r <= M) return query(l, r, k << 1, L, M);
        if (l > M) return query(l, r, k << 1 | 1, M+1, R);
        return op(query(l, M, k << 1, L, M),
                  query(M+1, r, k << 1 | 1, M+1, R));
    }
  public:
    SegTree(int _n) : n(_n) {
        t.assign((n+1) << 2, e); tag.assign((n+1) << 2, id);
    }
    void update(int l, int r, T val) {
        return update(l, r, val, 1, 0, n);
    }
    T query(int l, int r) {
        return query(l, r, 1, 0, n);
    }
};


namespace Simple { // simple segmentree: point modification & range query


template<class T>
class SegTree {
    int n;
    vector<T> t;
    const T e; // identity of op
    const function<T(T, T)> op;

    void update(int pos, int pl, int pr, int i, T val) {
        if (pl == pr) {
            t[pos] = val;
            return;
        }
        int m = (pl + pr)/2;
        if (i <= m) update(pos*2, pl, m, i, val);
        else update(pos*2+1, m+1, pr, i, val);
        t[pos] = op(t[pos*2], t[pos*2+1]);
    }
    T query(int pos, int pl, int pr, int l, int r) {
        if (l == pl && pr == r) {
            return t[pos];
        }
        int m = (pl + pr)/2;
        if (r <= m) return query(pos*2, pl, m, l, r);
        if (l > m) return query(pos*2+1, m+1, pr, l, r);
        return op(query(pos*2, pl, m, l, m), query(pos*2+1, m+1, pr, m+1, r));
    }

  public:
    SegTree(int _n, T _e, function<T(T, T)> _op) : n(_n), e(_e), op(_op) {
        t.assign(_n*4, e);
    }
    void update(int i, T val) {
        return update(1, 0, n, i, val);
    }
    T query(int l, int r) {
        return query(1, 0, n, l, r);
    }
};


} // namespace Simple


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    SegTree<ll> st(n, 0, [](ll x, ll y){return max(x, y)});
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        st.update(i, i, a);
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y, k;
            cin >> x >> y >> k;
            x--, y--;
            st.update(x, y, k);
        } else {
            int x, y;
            cin >> x >> y;
            x--, y--;
            cout << st.query(x, y) << nl;
        }
    }

    return 0;
}

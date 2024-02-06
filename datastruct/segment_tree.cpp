// https://www.luogu.com.cn/problem/P3372
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';

template <class T>
struct ST {
    int n, size;
    vector<T> tree, tag;

    /* TO FILL IN */
    const T e = 0;
    const bool acc = true; // accumulative (add or set on modification)
    T op(T a, T b) {
        return a + b;
    }
    T pow(T a, int n) {
        return a * n;
    }

    ST(int _n) : n(_n) {
        int i = 1;
        while (i < n) i <<= 1;
        size = (i << 1) - 1;
        tree.assign(size, e);
        tag.assign(size, e);
    }

    void pushdown(int c, int cmin, int cmax) {
        if (tag[c] == e) return;
        tree[c] = acc ? op(tree[c], pow(tag[c], cmax - cmin + 1)) : tag[c];
        if (c < size / 2) {
            tag[c * 2 + 1] = acc ? op(tag[c * 2 + 1], tag[c]) : tag[c];
            tag[c * 2 + 2] = acc ? op(tag[c * 2 + 2], tag[c]) : tag[c];
        }
        tag[c] = e;
    }
    
    void update(int c, int cmin, int cmax, int lo, int hi, T v) {
        pushdown(c, cmin, cmax);
        if (cmin >= lo && cmax <= hi) {
            tag[c] = acc ? op(tag[c], v) : v;
            pushdown(c, cmin, cmax);
            return;
        }
        if (cmin > hi || cmax < lo) return;
        int cmid = cmin + (cmax - cmin) / 2;
        update(c * 2 + 1, cmin, cmid, lo, hi, v);
        update(c * 2 + 2, cmid + 1, cmax, lo, hi, v);
        tree[c] = op(tree[c * 2 + 1], tree[c * 2 + 2]);
    }

    void update(int lo, int hi, T v) {
        update(0, 0, size / 2, lo, hi, v);
    }

    T query(int c, int cmin, int cmax, int lo, int hi) {
        pushdown(c, cmin, cmax);
        if (cmin >= lo && cmax <= hi) return tree[c];
        if (cmin > hi || cmax < lo) return e;
        int cmid = cmin + (cmax - cmin) / 2;
        return op(query(c * 2 + 1, cmin, cmid, lo, hi),
                query(c * 2 + 2, cmid + 1, cmax, lo, hi));
    }

    T query(int lo, int hi) {
        return query(0, 0, size / 2, lo, hi);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    ST<ll> st(n);
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

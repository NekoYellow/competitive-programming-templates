// https://loj.ac/p/130
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';

template <class T>
struct BIT {
    int n;
    vector<T> tree;
    /* TO FILL IN */
    const T e = 0;
    T op(T a, T b) { return a + b; }

    BIT(int _n) : n(_n) {
        tree.assign(n, e);
    }
    BIT(const vector<T>& _a) : n(_a.size()) {
        tree.assign(n, e);
        for (int i = 0; i < n; i++) {
            tree[i] = op(tree[i], _a[i]);
            int p = i | (i + 1);
            if (p < n) tree[p] = op(tree[p], tree[i]);
        }
    }
    void add(int i, T x) {
        for (; i < n; i = i | (i+1))
            tree[i] = op(tree[i], x);
    }
    T query(int i) { // prefix sum
        T sum = e;
        for (; i > -1; i = (i & (i+1)) - 1)
            sum = op(sum, tree[i]);
        return sum;
    }
};

namespace Simple {

template <class T>
struct BIT {
    int n;
    vector<T> t;

    BIT(int _n): n(_n) { t.assign(n+1, 0); }
    void add(int x, T v) {
        while (x <= n) t[x] += v, x += x & -x;
    }
    T query(int x) {
        T r = 0;
        while (x) r += t[x], x -= x & -x;
        return r;
    }
};




};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (auto &e: a)
        cin >> e;

    BIT<ll> tree(a);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int i, x;
            cin >> i >> x; i--;
            tree.add(i, x);
        } else {
            int l, r;
            cin >> l >> r; l--, r--;
            cout << tree.query(r) - tree.query(l-1) << nl;
        }
    }

    return 0;
}

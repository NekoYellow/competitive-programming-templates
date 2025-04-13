// https://loj.ac/p/130
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';

template <class T>
struct BIT { // Fenwick, 0-indexed
    int n;
    vector<T> tree;
    const T e;
    const function<T(T, T)> op;

    BIT(int _n, T _e, function<T(T, T)> _op) : n(_n), e(_e), op(_op) {
        tree.assign(n, e);
    }
    BIT(const vector<T>& _a, T _e, function<T(T, T)> _op) : n(_a.size()), e(_e), op(_op) {
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

namespace Simple { // 1-indexed

const int N = 2e6 + 1;

int n;
ll bit[N];

void add(int i, ll v) {
    for (; i <= n; i += i & -i) bit[i] += v;
}

ll query(int i) {
    ll res = 0;
    for (; i; i -= i & -i) res += bit[i];
    return res;
}

ll query(int l, int r) {
    return query(r) - query(l-1);
}


};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (auto &e: a)
        cin >> e;

    BIT<ll> tree(a, 0, [](ll x, ll y){return x+y;});

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

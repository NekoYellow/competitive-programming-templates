// https://codeforces.com/contest/1983/problem/D
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
    T op(T a, T b) {
        return a + b;
    }

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
        for (; i < n; i = i | (i+1)) {
            tree[i] = op(tree[i], x);
        }
    }

    T query(int i) { // prefix sum
        T sum = e;
        for (; i > -1; i = (i & (i+1)) - 1) {
            sum = op(sum, tree[i]);
        }
        return sum;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto &e: a) cin >> e;
    for (auto &e: b) cin >> e;

    vector<int> sa(a), sb(b);
    sort(sa.begin(), sa.end());
    sort(sb.begin(), sb.end());
    for (int i = 0; i < n; i++) {
        if (sa[i] != sb[i]) {
            cout << "NO" << nl;
            return;
        }
    }
    int mx = sa.back();
    sa.clear(), sb.clear();

    // count #inversions in v using binary-indexed tree
    auto cnt = [&](const vector<int>& v) {
        ll res = 0;
        BIT<int> t(mx+1); // mx := max(v)
        for (int i = 0; i < n; i++) {
            res += t.query(mx) - t.query(v[i]); // count(v[i]+1, mx)
            t.add(v[i], 1);
        }
        return res;
    };

    int na = cnt(a), nb = cnt(b);
    if (na%2 == nb%2) cout << "YES" << nl;
    else cout << "NO" << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

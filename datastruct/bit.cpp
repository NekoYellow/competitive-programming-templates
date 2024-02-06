// https://codeforces.com/gym/102800/problem/M
/* The 14th Jilin Provincial Collegiate Programming Contest, Problem M.
   Solve queries on array to return the xor sum of elements having even
   occurences in a[l..r].
   BIT (Bit-Indexed Tree) is used to track the prefix xor sum of unique
   elements in a.
*/
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
        return a ^ b;
    }

    BIT(int _n) : n(_n) {
        tree.assign(n+1, e);
    }

    BIT(const vector<T>& _a) {
        n = _a.size();
        tree.assign(n+1, e);
        for (int i = 0; i < n; i++) {
            add(i, _a[i]);
        }
    }

    int lowbit(int x) {
        return x & (-x);
    }

    void add(int i, T x) {
        ++i;
        while (i <= n) {
            tree[i] = op(tree[i], x);
            i += lowbit(i);
        }
    }

    T query(int i) {
        ++i;
        T sum = e;
        while (i) {
            sum = op(sum, tree[i]);
            i -= lowbit(i);
        }
        return sum;
    }
};

struct node {
    int l, r, i;
};

bool operator<(const node& a, const node& b) {
    return a.r < b.r;
}

void solve() {
    int n, q;
    cin >> n >> q;
    map<int, int> idx;
    vector<int> a(n), pre(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pre[i] = idx.find(a[i])==idx.end() ? -1 : idx[a[i]];
        idx[a[i]] = i;
    }
    vector<node> b(q);
    for (int i = 0; i < q; i++) {
        cin >> b[i].l >> b[i].r;
        b[i].l--, b[i].r--;
        b[i].i = i;
    }
    sort(b.begin(), b.end());

    BIT<int> tree(a);
    vector<int> ps(n+1, 0);
    for (int i = 0; i < n; i++) {
        ps[i+1] = ps[i]^a[i];
    }
    int p = 0;
    vector<int> ans(q);
    for (auto [l, r, i]: b) {
        for (; p <= r; p++) {
            if (~pre[p]) tree.add(pre[p], a[p]);
        }
        ans[i] = ps[r+1]^ps[l] ^ tree.query(r)^tree.query(l-1);
    }
    for (auto e: ans) {
        cout << e << nl;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}
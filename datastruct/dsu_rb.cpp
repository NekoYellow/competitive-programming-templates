// https://acm.hdu.edu.cn/showproblem.php?pid=7436
#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int N = 6e5 + 1;

int par[N], sz[N], st[N], sp; // parent, size, stack
ll tag[N];
void init(int n) {
    for (int i = 1; i <= n; i++)
        par[i] = i, sz[i] = 1;
}
int find(int x) {
    return par[x] == x ? x : find(par[x]);
}
void merge(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return;
    if (sz[x] > sz[y]) swap(x, y);
    tag[x] -= tag[y];
    par[x] = y;
    sz[y] += sz[x];
    st[++sp] = x;
}
void rollback(int prev) {
    while (sp > prev) {
        int x = st[sp--];
        int px = par[x];
        tag[x] += tag[px];
        sz[px] -= sz[x];
        par[x] = x;
    }
}

namespace Encapsulation {

struct DSU { // Revertable DSU
    vector<int> p, sz, st; // parent, size, stack
    vector<ll> tag; // data on nodes
    DSU(int n) {
        p.resize(n); iota(p.begin(), p.end(), 0);
        sz.assign(n, 1); tag.assign(n, 0);
    }

    int find(int x) { // no path compression
        return (x == p[x] ? x : find(p[x]));
    }
    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        p[y] = x; sz[x] += sz[y];
        st.push_back(y); tag[y] -= tag[x];
    }

    int size() { return st.size(); } // stack pointer
    void rollback(int last) { // roll back to last sp
        while (size() > last) {
            int y = st.back();
            int x = p[y];
            p[y] = y; sz[x] -= sz[y];
            st.pop_back(); tag[y] += tag[x];
        }
    }

    void add(int x, int v) { tag[x] += v; } // add v to node x
};

} // namespace Encapsulation

vector<pair<int, int>> t[N << 2];
void update(int p, int l, int r, int ql, int qr, int a, int b) {
    if (ql <= l && r <= qr) {
        t[p].emplace_back(a, b);
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) update(p << 1, l, mid, ql, qr, a, b);
    if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, a, b);
}
void query(int p, int l, int r) {
    if (l == r) {
        int last = sp;
        for (auto [x, y] : t[p]) merge(x, y);
        tag[find(1)] += l;
        rollback(last);
        return;
    }
    int mid = (l + r) >> 1;
    int last = sp;
    for (auto [x, y] : t[p]) merge(x, y);
    query(p << 1, l, mid); query(p << 1 | 1, mid + 1, r);
    rollback(last);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    while (m--) {
        int a, b, l, r;
        cin >> a >> b >> l >> r;
        update(1, 1, n, l, r, a, b);
    }
    init(n);
    query(1, 1, n);
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans ^= tag[i];
    cout << ans << '\n';

    return 0;
}
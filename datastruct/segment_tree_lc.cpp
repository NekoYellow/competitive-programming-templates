// https://acm.hdu.edu.cn/showproblem.php?pid=7537
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pli = pair<ll, int>;

const int N = 1e5 + 7, K = 3;

struct Line {
    int k, b, id;
    Line() : k(0), b(0), id(0) {}
    Line(int k, int b, int id) : k(k), b(b), id(id) {}
    ll val(int x) { return 1ll * k*x + b; }
} tr[K][N<<2]; // each node is top K lines

int m; // range of segtree is [1, m]

#define le(x) (x << 1)
#define ri(x) (x << 1 | 1)

bool gt(Line a, Line b, int x) {
    return a.val(x) > b.val(x);
}
// insert f(x)=kx+b, 1<=x<=m
void insert(Line v, int k=1, int l=1, int r=m) {
    int mid = (l + r) >> 1;
    for (int i = 0; i < K; i++) {
        if (gt(v, tr[i][k], mid)) swap(tr[i][k], v);
    }
    bool lf = false, rf = false;
    for (int i = 0; i < K; i++) {
        if (!lf && gt(v, tr[i][k], l))
            insert(v, le(k), l, mid), lf = true;
        if (!rf && gt(v, tr[i][k], r))
            insert(v, ri(k), mid+1, r), rf = true;
    }
}
// query the top k-th line f's that maximizes f(x)
void query(array<Line, K> &res, int x, int k=1, int l=1, int r=m) {
    for (int i = 0; i < K; i++) {
        Line line = tr[i][k];
        for (int j = 0; j < K; j++) {
            if (gt(line, res[j], x)) swap(line, res[j]); 
        }
    }
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) query(res, x, le(k), l, mid);
    else query(res, x, ri(k), mid+1, r);
}

void solve() {
    memset(tr, 0, sizeof(tr));
    int n;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int a, b; cin >> a >> b;
        insert({b, a, i});
    }

    vector<array<pli, K>> dp(m+1);
    for (int x = 1; x <= m; x++) {
        array<Line, K> res;
        query(res, x);
        for (int i = 0; i < K; i++) {
            for (auto [pval, pid]: dp[x-1]) {
                if (res[i].id && res[i].id != pid) {
                    dp[x][i] = max(dp[x][i], {pval+res[i].val(x), res[i].id});
                }
            }
        }
    }
    cout << max_element(dp[m].begin(), dp[m].end())->first << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    for (; T; T--) solve();
    return 0;
}
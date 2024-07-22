// https://acm.hdu.edu.cn/showproblem.php?pid=7450
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

struct frac {
    ll u, d;
    frac(ll up=0, ll down=1) : u(up), d(down) {}
};
frac operator+(const frac &x, const frac &y) {
    ll d = x.d / gcd(x.d, y.d) * y.d;
    return frac(x.u * (d / x.d) + y.u * (d / y.d), d);
}
bool operator<(const frac &x, const frac &y) {
    return x.u*y.d < y.u*x.d;
}
void reduce(frac &x) {
    ll f = gcd(x.u, x.d); x.u /= f, x.d /= f;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        g[u].push_back(v); g[v].push_back(u);
    }
    vector<frac> days(n);
    for (int i = 0; i < n; i++) {
        int u; cin >> u;
        assert(1 <= u && u <= 15); // p = u/15
        days[i] = frac(15, u); // E(#days), where #days ~ Geom(p)
    }
    vector<frac> dp(n);
    auto dfs = [&](auto self, int u, int p) -> void {
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            if (dp[u] < dp[v]) dp[u] = dp[v];
        }
        dp[u] = dp[u] + days[u];
        reduce(dp[u]);
    };
    dfs(dfs, 0, -1);
    cout << dp[0].u << '/' << dp[0].d << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}
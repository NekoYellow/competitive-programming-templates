#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// count number of subarrays sa satisfying
// reduce(&, sa) == k
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &e: a) cin >> e;

    ll ans = 0;
    map<int, int> dp; // cnt
    for (auto e: a) {
        map<int, int> ndp;
        for (auto [k, v]: dp)
            ndp[k & e] += v;
        ndp[e]++;
        ans += ndp[k];
        dp = ndp;
    }
    cout << ans << '\n';
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
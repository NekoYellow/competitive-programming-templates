#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';

ll sum(const vector<vector<ll>> &a, int u, int d, int l, int r) {
    // return sum of the submatrix [u,d]x[l,r] of a (a is pre-processed)
    return a[d][r] - a[u-1][r] - a[d][l-1] + a[u-1][l-1];
}

void solve() {
    int n, m, h, w;
    cin >> n >> m >> h >> w;
    vector<vector<ll>> a(n+1, vector<ll>(m+1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
    	    cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            a[i][j] += a[i][j-1];
        }
    }
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            a[i][j] += a[i-1][j];
        }
    }
    if (a[n][m] <= 0) {
    	cout << "NO" << nl;
    	return;
    }
    for (int i = 0; i+h <= n; i++) {
        for (int j = 0; j+w <= m; j++) {
    	    if (sum(a, i+1, i+h, j+1, j+w) >= 0) {
    		    cout << "NO" << nl;
    		    return;
    	    }
        }
    }
    cout << "YES" << nl;
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

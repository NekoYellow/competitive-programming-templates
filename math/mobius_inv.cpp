// https://www.luogu.com.cn/problem/P2158
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';

// Mobius Inversion: $\Sigma_{i=1}^{n-1}\Sigma_{j=1}^{n-1}[GCD(i, j)==1] = \Sigma_{i=1}^{n-1}\Sigma_{j=1}^{n-1}\Sigma_{g | gcd(i, j)}\mu(i)$
// count #pairs (x, y) in [1, N-1]x[1, N-1] having gcd(x, y) = 1
signed main() {
    int n;
    cin >> n; n--;
    if (!n) {
        cout << 0 << nl;
        return 0;
    }
    vector<int> mu(n+1), primes;
    vector<bool> vis(n+1);
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) primes.push_back(i), mu[i] = -1;
        for (auto j: primes) {
            int nw = i*j;
            if (nw > n) break;
            vis[nw] = 1;
            if (i%j == 0) break;
            mu[nw] = -mu[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        mu[i] += mu[i-1];
    }
    int ans = 2; // special case: (0, 1) and (1, 0)
    for (int l = 1, r; l <= n; l = r+1) {
        r = n / (n/l);
        ans += (mu[r] - mu[l-1]) * (n/l) * (n/r);
    }
    cout << ans << nl;
    return 0;
}

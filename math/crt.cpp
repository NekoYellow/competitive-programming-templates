/*Luogu-P1495
Solving equation system
    x = a1 (mod r1)
    x = a2 (mod r2)
    ...
    x = an (mod rn)
via CRT(Chinese Remainder Theorem).
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const char nl = '\n';

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

ll crt(const vector<ll> &a, const vector<ll> &r) {
    int k = a.size()-1; // number of equations
    ll n = 1, ans = 0;
    for (int i = 1; i <= k; i++) n *= r[i];
    for (int i = 1; i <= k; i++) {
        ll m = n / r[i], b, y;
        exgcd(m, r[i], b, y);  // b * m mod r[i] = 1
        ans = (ans + a[i] * m * b % n) % n;
    }
    return (ans % n + n) % n;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<ll> a(n+1), r(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> r[i] >> a[i];
    }
    cout << crt(a, r) << nl;
    return 0;
}

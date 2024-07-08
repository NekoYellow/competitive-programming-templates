// https://www.luogu.com.cn/problem/P1495
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';

/* Solving equation system
    x = a1 (mod r1)
    x = a2 (mod r2)
    ...
    x = an (mod rn)
via CRT(Chinese Remainder Theorem).
*/
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
    ll n = 1;
    __int128 ans = 0;
    for (auto e: r) n *= e;
    for (int i = 0; i < a.size(); i++) {
        ll m = n/r[i], b, y;
        exgcd(m, r[i], b, y);  // get b = inv(m) (b*m mod r[i] = 1)
        while (b < 0) b += r[i];
        ans = (ans + (__int128)a[i] * m * b % n) % n;
    }
    return ans;
}
signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<ll> a(n), r(n); // gcd(r) = 1
    for (int i = 0; i < n; i++)
        cin >> r[i] >> a[i];
    cout << crt(a, r) << nl;
    return 0;
}

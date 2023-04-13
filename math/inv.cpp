/* Luogu-P3811 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll P = 1e9+7;

ll qpow(ll a, ll n, ll p = P) {
    a = (p + a % p) % p;
    ll res = 1;
    while (n) {
        if (n & 1) res = res * a % p;
        a = a * a % p;
        n >>= 1;
    }
    return res;
}

// calculate inverse via quick-power (a^-1 = a^(p-2) (mod p))
ll inv_f(ll a, ll p = P) {
    return qpow(a, p-2, p);
}

// calculate inverse of 1~n in O(n) time
ll inv[(int)(1e7+10)];
void calc_inv(ll n, ll p = P) {
    inv[1] = 1; cout << 1 << '\n';
    for (ll i = 2; i <= n; i++) {
        inv[i] = (p - p/i) * inv[p % i] % p;
        cout << inv[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    ll n, p;
    cin >> n >> p;
    calc_inv(n, p);
    return 0;
}
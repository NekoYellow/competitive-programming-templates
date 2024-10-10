// https://www.luogu.com.cn/problem/P4718
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

ll qmul(ll a, ll b, ll m) {
    ull c = (ull)a * (ull)b - (ull)((long double)a / m * b + 0.5L) * (ull)m;
    if (c < (ull)m) return c;
    return c + m;
}

ll qpow(ll x, ll p, ll m) {
    ll ans = 1;
    for (; p; p >>= 1, x = qmul(x, x, m)) {
        if (p & 1) ans = qmul(ans, x, m);
    }
    return ans;
}

bool Miller_Rabin(ll p) { // prime test
    if (p < 2) return false;
    if (p == 2 || p == 3) return true;
    ll d = p - 1, r = 0;
    while (!(d & 1)) ++r, d >>= 1; // process d to odd
    for (ll k = 0; k < 10; ++k) {
        ll a = rnd() % (p - 2) + 2;
        ll x = qpow(a, d, p);
        if (x == 1 || x == p - 1) continue;
        for (int i = 0; i < r - 1; ++i) {
            x = qmul(x, x, p);
            if (x == p - 1) break;
        }
        if (x != p - 1) return false;
    }
    return true;
}

ll Pollard_Rho(ll x) { // get a non-trivial factor
    ll s = 0, t = 0;
    ll c = rnd() % (x - 1) + 1;
    ll val = 1;
    for (int goal = 1; ; goal <<= 1, s = t, val = 1) {
        for (int step = 1; step <= goal; ++step) {
            t = (qmul(t, t, x) + c) % x;
            val = qmul(val, abs(t - s), x);
            if ((step % 127) == 0) {
                ll d = gcd(val, x);
                if (d > 1) return d;
            }
        }
        ll d = gcd(val, x);
        if (d > 1) return d;
    }
}

ll maxfac(ll x) {
    if (x < 2) return 0;
    if (Miller_Rabin(x)) { // x is prime
        return x;
    }
    ll p = x;
    while (p >= x) p = Pollard_Rho(x);
    while (!(x % p)) x /= p;
    return max(maxfac(x), maxfac(p));
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        ll mx = maxfac(n);
        if (mx == n)
            cout << "Prime\n";
        else
            cout << mx << '\n';
    }
    return 0;
}
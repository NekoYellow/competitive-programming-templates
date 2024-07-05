// https://codeforces.com/contest/1931/problem/G
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';

template<class T>
constexpr T power(T a, ll n) {
    T res = 1;
    for (; n; a = a*a, n >>= 1) {
        if (n & 1) res = res*a;
    }
    return res;
}

template<int P>
struct MInt {
    int x;
    constexpr MInt() : x() {}
    constexpr MInt(ll _x) : x(_x % P) { if (x < 0) x += P; }
    constexpr int val() const { return x; }
    explicit constexpr operator int() const { return x; }
    constexpr MInt operator-() const {
        return P - x;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    friend constexpr MInt operator+(const MInt& lhs, const MInt& rhs) {
        return MInt(lhs.x + rhs.x);
    }
    friend constexpr MInt operator-(const MInt& lhs, const MInt& rhs) {
        return lhs + (-rhs);
    }
    friend constexpr MInt operator*(const MInt& lhs, const MInt& rhs) {
        return MInt(1LL * lhs.x * rhs.x);
    }
    friend constexpr MInt operator/(const MInt& lhs, const MInt& rhs) {
        return lhs * rhs.inv();
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        ll v; is >> v; a = v;
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(const MInt& lhs, const MInt& rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(const MInt& lhs, const MInt& rhs) {
        return lhs.val() != rhs.val();
    }
};
/* TO FILL IN */
constexpr int P = 998244353;
using Z = MInt<P>;

struct Comb {
    int _n;
    std::vector<Z> _fac, _invfac, _inv;

    Comb() : _n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() { init(n); }

    void init(int m) {
        m = std::min(m, P - 1);
        if (m <= _n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        for (int i = _n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > _n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        _n = m;
    }

    Z fac(int m) {
        if (m > _n) init(2 * m);
        return _fac[m];
    }
    Z invfac(int m) {
        if (m > _n) init(2 * m);
        return _invfac[m];
    }
    Z inv(int m) {
        if (m > _n) init(2 * m);
        return _inv[m];
    }
    Z binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;

Z big_choose(int n, int m) { // for large n
    m = min(m, n-m);
    Z res = 1;
    for (int v = n-m+1; v <= n; v++) {
        res = res * v;
    }
    res = res * comb.invfac(m);
    return res;
}

void solve() {
    int i, d, h, l; // incr, decr, high, low
    cin >> i >> d >> h >> l;

    if (abs(i-d) > 1) {
        cout << 0 << nl;
        return;
    } else if (i == 0 && d == 0) {
        if (h != 0 && l != 0) {
            cout << 0 << nl;
            return;
        }
        cout << 1 << nl;
        return;
    } else if (i == 0 || d == 0) {
        cout << 1 << nl;
        return;
    }

    // Similar to B-E Distribution
    int p = max(i, d);
    Z ans = 0;
    if (i == d) {
        ans = ans + comb.binom(p+h-1, p-1) * comb.binom(p+l, p); // i-d-...-i-d
        ans = ans + comb.binom(p+h, p) * comb.binom(p+l-1, p-1); // d-i-...-d-i
    } else {
        ans = comb.binom(p+h-1, p-1) * comb.binom(p+l-1, p-1);
    }
    cout << ans << nl;
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
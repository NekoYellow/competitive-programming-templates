// https://codeforces.com/contest/1924/problem/E
#include <bits/stdc++.h>

using ll = long long;

template<class T>
constexpr T power(T a, ll b) {
    T res = 1;
    for (; b; b >>= 1, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}

template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(ll _x) : x{_x % P} { if (x < 0) x += P; }
    constexpr static int getMod() { return P; }
    constexpr int val() const { return x; }
    explicit constexpr operator int() const { return x; }
    constexpr MInt operator-() const { return MInt(P - x); }
    constexpr MInt inv() const { assert(x != 0); return power(*this, P - 2); }
    friend constexpr MInt operator+(const MInt& lhs, const MInt& rhs) { return MInt(lhs.x + rhs.x); }
    friend constexpr MInt operator-(const MInt& lhs, const MInt& rhs) { return lhs + (-rhs); }
    friend constexpr MInt operator*(const MInt& lhs, const MInt& rhs) { return MInt(1LL * lhs.x * rhs.x); }
    friend constexpr MInt operator/(const MInt& lhs, const MInt& rhs) { return lhs * rhs.inv(); }
    constexpr MInt &operator+=(const MInt& rhs) & { x = (x + rhs.x) % P; return *this; }
    constexpr MInt &operator-=(const MInt& rhs) & { return *this += -rhs; }
    constexpr MInt &operator*=(const MInt& rhs) & { x = 1LL * x * rhs.x % P; return *this; }
    constexpr MInt &operator/=(const MInt& rhs) & { return *this *= rhs.inv(); }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        ll v; is >> v; a = MInt(v); return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) { return os << a.val(); }
    friend constexpr bool operator==(const MInt& lhs, const MInt& rhs) { return lhs.val() == rhs.val(); }
    friend constexpr bool operator!=(const MInt& lhs, const MInt& rhs) { return lhs.val() != rhs.val(); }
};

/* TO FILL IN */
constexpr int P = 1E9 + 7;
using Z = MInt<P>;

struct Comb {
    int _n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;
    
    Comb() : _n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() { init(n); }
    
    void init(int m) {
        m = std::min(m, Z::getMod() - 1);
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

void solve() {
    int n, m;
    ll k;
    std::cin >> n >> m >> k;
    
    if (1LL * n * m < k) {
        std::cout << 0 << "\n";
        return;
    }
    
    Z ans = 1;
    for (int i = 1; i < n; i++) {
        if (1LL * i * m >= k) {
            ans += comb.inv(i + m - 1);
        }
    }
    for (int i = 1; i < m; i++) {
        if (1LL * i * n >= k) {
            ans += comb.inv(i + n - 1);
        }
    }
    for (int s = 2, i = -1; s <= n + m - 2; s++) {
        if (1LL * (s / 2) * ((s + 1) / 2) < k) {
            continue;
        }
        if (i == -1) {
            i = s / 2;
        }
        while (1LL * (i - 1) * (s - (i - 1)) >= k) {
            i -= 1;
        }
        int l = std::max(i, s - (m - 1));
        int r = std::min(s - i, n - 1);
        ans += std::max(0, r - l + 1) * comb.inv(s) * comb.inv(s - 1) * 2;
    }
    
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
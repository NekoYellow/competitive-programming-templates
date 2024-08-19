// https://atcoder.jp/contests/abc212/tasks/abc212_h
#include <bits/stdc++.h>
using namespace std;

template<class T> constexpr T power(T a, int n) {
    T res = 1;
    for (; n; a = a*a, n >>= 1) if (n & 1) res = res*a;
    return res;
}
template<int P>
struct MInt {
    int x;
    constexpr MInt() : x(0) {}
    constexpr MInt(long long _x) : x(_x % P) { if (x < 0) x += P; }
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
};

constexpr int P = 998244353;
using mint = MInt<P>;
using V = vector<mint>;
#define rep(i, N) for (int i = 0; i < (int)(N); i++)

void hadamard(V& f) { // FWT $C_k = \sum_{k=i\oplus j}A_iB_j$
    int n = f.size(); // typically power of 2
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j++) {
            if (!(j & i)) {
                auto x = f[j], y = f[j | i];
                f[j] = x + y, f[j | i] = x - y;
            }
        }
    }
}

V operator+(const V& a, const V& b) {
    V c(a.size());
    rep(i, a.size()) c[i] = a[i] + b[i];
    return c;
}
V operator*(V a, V b) {
    hadamard(a), hadamard(b);
    rep(i, a.size()) a[i] = a[i] * b[i];
    hadamard(a);
    auto inv = mint(a.size()).inv();
    rep(i, a.size()) a[i] = a[i] * inv;
    return a;
}

pair<V, V> calc(int n, const V& X) { // X+X^2+...+X^n
    if (n == 1) return {X, X};
    auto [S, F] = calc(n / 2, X); // S = X+X^2+...+X^(n/2), F = X^(n/2)
    S = S * F + S, F = F * F;
    if (n & 1) S = S * X + X, F = F * X;
    return {S, F};
}

const int MX = 1 << 16;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k, x;
    cin >> n >> k;
    V X(MX);
    rep(_, k) cin >> x, X[x] = 1;
    auto [S, _] = calc(n, X);
    cout << accumulate(begin(S) + 1, end(S), mint(0)).val() << "\n";

    return 0;
}

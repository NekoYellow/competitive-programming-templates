// Use matrix binary power to accelerate calculating recurrence eq
#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<class T>
constexpr T power(T a, ll n) {
    T res;
    for (; n; a = a*a, n >>= 1) {
        if (n & 1) res = res*a;
    }
    return res;
}

template<class T>
struct M { // 2x2 Matrix
    T a, b, c, d; // [[a, b], [c, d]]
    M() : a(1), b(0), c(0), d(1) {}
    M(T _a, T _b, T _c, T _d) : a(_a), b(_b), c(_c), d(_d) {}
    friend constexpr M operator*(const M& l, const M& r) {
        return M(l.a*r.a + l.b*r.c, l.a*r.b + l.b*r.d,
                 l.c*r.a + l.d*r.c, l.c*r.b + l.d*r.d);
    }
};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int T; cin >> T;
    while (T--) {
        int n; // print the n-th fibonacci number
        cin >> n;
        M t = power(M(1, 1, 1, 0), n-1);
        cout << t.a * 1 + t.b * 0 << '\n';
    }

    return 0;
}
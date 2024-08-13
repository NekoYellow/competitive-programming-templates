// https://ac.nowcoder.com/acm/contest/81604/H
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pt = complex<ll>;

ll dot(pt p, pt q)  {
    return real(conj(p) * q);
}
ll cross(pt p, pt q) {
    return imag(conj(p) * q);
}
bool above(pt p) {
    return imag(p) > 0 || (imag(p) == 0 && real(p) > 0);
}

void polygonize(vector<pt> &v) {
    int l = 0, n = v.size();
    for (int i = 0; i < n; i++) {
        if (above(v[l] - v[i])) l = i;
    }
    swap(v[0], v[l]);
    sort(next(begin(v)), end(v), [&](pt a, pt b) {
        a -= v[0], b -= v[0];
        if (above(a) != above(b)) return above(a);
        return cross(a, b) > 0;
    }); // sort into ccw order
    v.push_back(v.front());
}

// perimeter
ld polyP(const vector<pt> &a) { // a: a polygon in ccw order
    ld peri = 0; assert(a.front() == a.back());
    for (auto it = a.begin(); next(it) != a.end(); it++) {
        pt p = *it, q = *next(it);
        peri += sqrtl(dot(q-p, q-p));
    }
    return peri;
}
// longest distance between some pair of points on a convex polygon
ld polyD(const vector<pt> &a) { // a: a polygon in ccw order
    ll d2 = 0; assert(a.front() == a.back());
    for (auto it = a.begin(), it2 = next(it); next(it) != a.end(); it++) {
        pt p = *it, q = *next(it);
        for (; next(it2) != a.end(); it2++) {
            pt cur = *it2, nxt = *next(it2);
            d2 = max(d2, dot(cur - p, cur - p));
            ll sz = abs(cross(p - cur, q - cur));
            ll nsz = abs(cross(p - nxt, q - nxt));
            if (sz > nsz) break;
        }
    }
    return sqrtl(d2);
}

const ld pi = acos(-1);

inline void solve() {
    int n, m;
    cin >> n;

    vector<pt> a(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[i] = {x, y};
    }
    a.push_back(a.front());
    cin >> m;
    vector<pt> b(m);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        b[i] = {x, y};
    }
    b.push_back(b.front());

    // polygonize(a); polygonize(b);

    ld ans = polyP(a) + 2 * pi * polyD(b);
    cout << fixed << setprecision(12) << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;
    for (; t; t--) solve();

    return 0;
}
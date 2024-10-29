// https://codeforces.com/gym/105459/problem/B
#include <bits/stdc++.h>
using namespace std;
using T = long long;
const T eps = 0;

struct Point {
    T x, y;
    int id;
    Point() = default;
    Point(T x, T y) : x(x), y(y) {}
    Point operator+(const Point &a) const { return {x + a.x, y + a.y}; }
    Point operator-(const Point &a) const { return {x - a.x, y - a.y}; }
    Point operator*(const T &a) const { return {a * x, a * y}; }
    Point operator/(const T &a) const { return {a / x, a / y}; }
    T operator*(const Point &a) const { return x * a.x + y * a.y; }
    T operator^(const Point &a) const { return x * a.y - y * a.x; }
    int toleft(const Point &a) const { auto t = (*this) ^ a; return (t > 0) - (t < 0); }
    bool operator<(const Point &a) const { return x == a.x ? y < a.y : x < a.x; }
};
using VP = vector<Point>;

VP convex(VP p) {
#define back1(x) x.back()
#define back2(x) *next(x.rbegin())
    VP st;
    sort(p.begin(), p.end());
    for (auto u : p) {
        while (st.size() > 1 && (back1(st) - back2(st)).toleft(u - back2(st)) <= 0)
            st.pop_back();
        st.push_back(u);
    }
    auto k = st.size();
    p.pop_back(); reverse(p.begin(), p.end());
    for (auto u : p) {
        while (st.size() > k && (back1(st) - back2(st)).toleft(u - back2(st)) <= 0)
            st.pop_back();
        st.push_back(u);
    }
    if (st.size() > 1) st.pop_back();
    return st;
}

int nxt(int i, int n) { return (i + 1 == n) ? 0 : i + 1; }

// find the maximum area of a concave polygon among n points
void solve() {
    int n;
    cin >> n;

    VP p;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        p.emplace_back(x, y);
        p.back().id = i - 1;
    }
    auto C = convex(p);
    vector<int> vis(n, 0);
    for (auto u : C)
        vis[u.id] = 1;

    VP p2;
    for (int i = 0; i < n; i++)
        if (!vis[i]) p2.push_back(p[i]);
    if (p2.empty()) {
        cout << -1 << '\n';
        return;
    }
    auto C2 = convex(p2);

    T S = 0;
    for (int i = 0; i < (int)C.size(); i++)
        S += (C[i] ^ (C[(i + 1) % C.size()]));
    S = abs(S);

    T ans = 0;
    int j = 0;
    for (int i = 0; i < (int)C.size(); i++)
    {
        auto vi = C[nxt(i, C.size())] - C[i];
        while (abs((C2[nxt(j, C2.size())] - C[i]) ^ vi) < abs((C2[j] - C[i]) ^ vi))
            j = nxt(j, C2.size());
        ans = max(ans, S - abs((C2[j] - C[i]) ^ vi));
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}

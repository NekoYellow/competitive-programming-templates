// https://codeforces.com/contest/510/problem/D
#include <bits/stdc++.h>
using namespace std;

/* Bezout's Lemma + Bag DP
Bezout's Lemma: for integers a,b (ab!=0) exist x,y so that ax+by=gcd(a,b).
=> when gcd(a,b)=1, exist x,y : ax+by=1. */
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> l(n), c(n);
    for (int i = 0; i < n; i++) cin >> l[i];
    for (int i = 0; i < n; i++) cin >> c[i];
    map<int, int> f; // less space compared with array
    f[0] = 0; // start point; gcd(0, x) = x
    for (int i = 0; i < n; i++) {
        for (auto [pred, cost]: f) { // iterate prev-d from small to large
            int d = gcd(pred, l[i]);
            if (!f.count(d)) f[d] = cost + c[i];
            else f[d] = min(f[d], cost + c[i]);
        }
    }
    if(!f.count(1)) f[1] = -1; // 1 is not reachable
    cout << f[1] << '\n';
    return 0;
}

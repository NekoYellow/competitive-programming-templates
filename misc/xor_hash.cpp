// https://codeforces.com/contest/1996/problem/G
// XOR Hashing.
#include <bits/stdc++.h>
using namespace std;
using ul = unsigned long long;

mt19937_64 rng;
// Given a loop graph with n nodes, and m pairs required to be
// accessible from one to another, find the minimum edges needed
void solve() {
    int n, m;
    cin >> n >> m;
    vector<ul> f(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v; u--, v--;
        ul x = rng();
        f[u] ^= x, f[v] ^= x; // tag b-a edges in [a, b)
    }
    for (int i = 1; i < n; i++) {
        f[i] ^= f[i-1];
    }
    map<ul, int> cnt;
    int gap = 0; // gap is the maximum count of some tag comb
    for (int i = 0; i < n; i++) {
        gap = max(gap, ++cnt[f[i]]);
    }
    cout << n - gap << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}

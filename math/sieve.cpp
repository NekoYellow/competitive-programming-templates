// https://www.luogu.com.cn/problem/P3383
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const char nl = '\n';

vector<int> primes, minp;

void sieve(int h) {
    primes.clear(); minp.assign(h+1, 0);
    for (int i = 2; i <= h; i++) {
        if (!minp[i]) primes.push_back(i), minp[i] = i;
        for (auto p: primes) {
            if (i*p > h) break;
            minp[i*p] = p;
            if (p == minp[i]) break;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    sieve(n);
    while (q--) {
        int i;
        cin >> i;
        cout << primes[i-1] << nl;
    }
    return 0;
}

/* Luogu-P1226 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll qpow(ll a, ll n, ll M) {
    ll res = 1;
    while (n) {
        if (n&1) res = res * a % M;
        a = a * a % M;
        n >>= 1;
    }
    return res;
}

int main() {
    ll a, n, m;
    cin >> a >> n >> m;
    cout << a << '^' << n << " mod " << m << "=" << qpow(a, n, m) << endl;
    return 0;
}

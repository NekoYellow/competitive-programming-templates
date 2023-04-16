/* Luogu-P5656
Solve indefinite equation ax + by = c via exgcd.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const char nl = '\n';

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        ll a, b, c;
        cin >> a >> b >> c;
        ll x, y;
        ll d = exgcd(a, b, x, y);
        if (c % d) {
            cout << -1 << nl;
            continue;
        }
        a /= d, b /= d, c /= d;
        x = (c*x % b + b)%b; if (x == 0) x = b;
        y = (c*y % a + a)%a; if (y == 0) y = a;
        if (c - a*x > 0) cout << (c-a*x-b*y)/a/b+1 << ' ' 
            << x << ' ' << y << ' ' << (c-b*y)/a << ' ' << (c-a*x)/b;
        else cout << x << ' ' << y;
        cout << nl;
    }
    return 0;
}

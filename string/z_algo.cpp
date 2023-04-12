/* Luogu-P5410 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> z_function(const string &s) {
    int n = s.length();
    vector<int> z(n);
    z[0] = n; // unconventional
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r && z[i-l] < r-i+1) {
            z[i] = z[i-l];
        } else {
            z[i] = max(0, r-i+1);
            while (i+z[i] < n && s[z[i]] == s[i+z[i]]) ++z[i];
        }
        if (i+z[i]-1 > r) l = i, r = i+z[i]-1;
    }
    return z;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string a, b;
    cin >> a >> b;
    auto z = z_function(b);
    ll ans = 0;
    for (int i = 0; i < z.size(); i++) {
        ans ^= 1LL*(i+1)*(z[i]+1);
    }
    cout << ans << endl;
    auto p = z_function(b+'#'+a);
    ans = 0;
    for (int i = 1; i <= a.size(); i++) {
        ans ^= 1LL*i*(p[b.size()+i]+1);
    }
    cout << ans << endl;
}

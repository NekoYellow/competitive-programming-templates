/* Luogu-P3383
Euler-sieve
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const char nl = '\n';

vector<int> primes;
vector<bool> np; // np[i] means i is not prime

void findprime(int hi) {
    np.resize(hi+1);
    for (int i = 2; i <= hi; i++) {
        if (!np[i]) primes.push_back(i);
        for (auto j: primes) {
            if (i*j > hi) break;
            np[i*j] = true;
            if (i%j == 0) break;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    findprime(n);
    while (q--) {
        int i;
        cin >> i;
        cout << primes[i-1] << nl;
    }
    return 0;
}

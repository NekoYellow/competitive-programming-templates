/* POJ-2406 Multi-Key Prefix Hash */
#include <iostream>
#include <algorithm>
#define FI first
#define SE second
using namespace std;
typedef long long ll;
#define PLL pair<ll,ll>
const int N = 1e6+10;
const PLL B = make_pair(37, 131), M = make_pair(1e9+7, 998244353);

PLL p[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string s;
    while (1) {
        cin >> s;
        if (s == ".") break;
        int n = s.size();
        p[0] = make_pair(0, 0);
        for (int i = 1; i <= n; i++) {
            p[i].FI = (p[i-1].FI*B.FI + s[i-1])%M.FI;
            p[i].SE = (p[i-1].SE*B.SE + s[i-1])%M.SE;
        }
        PLL c = make_pair(1, 1);
        int l = 1;
        for (; l*2 <= n; l++) {
            c.FI = c.FI*B.FI%M.FI; c.SE = c.SE*B.SE%M.SE;
            if (n%l) continue;
            bool flag = true;
            for (int i = l; i <= n-l; i += l) {
                ll h1 = p[i+l].FI - p[i].FI * c.FI % M.FI;
                if (h1 < 0) h1 += M.FI;
                if (p[l].FI != h1) flag = false;
                ll h2 = p[i+l].SE - p[i].SE * c.SE % M.SE;
                if (h2 < 0) h2 += M.SE;
                if (p[l].SE != h2) flag = false;
                if (!flag) break;
            }
            if (flag) {
                cout << n/l << '\n';
                break;
            }
        }
        if (l*2 > n) cout << "1\n";
    }
    return 0;
}

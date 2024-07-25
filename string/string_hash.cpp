// https://acm.hdu.edu.cn/showproblem.php?pid=7433
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

class Hash {
  public:
    Hash(const string& s) : n(s.size()), h(n+1), pw(n+1) {
        pw[0][0] = pw[0][1] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2; j++) {
                h[i+1][j] = h[i][j]*p[j] % m[j] + s[i];
                pw[i+1][j] = pw[i][j]*p[j] % m[j];
            }
        }
    }
    const pll get(int l, int r) { // get hash(s[l..r])
        assert(0 <= l && l <= r && r < n);
        array<ll, 2> res;
        for (int j = 0; j < 2; j++) {
            res[j] = h[r+1][j] - h[l][j]*pw[r-l+1][j] % m[j];
            res[j] = (res[j] + m[j]) % m[j];
        }
        return {res[0], res[1]};
    }
  private:
    int n, p[2] = {37, 233}, m[2] = {998244353, 1000000007};
    vector<array<ll, 2>> pw, h;
};

void solve() { // count how many substrs of t are in cycle(s)
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();

    Hash hs(s+s), ht(t);
    set<pll> pat; // cycle(s)
    for (int i = 0; i < n; i++) {
        pat.emplace(hs.get(i, i+n-1));
    }

    int ans = 0;
    for (int i = 0; i < m-n+1; i++) { // length-n substrs of t
        ans += pat.count(ht.get(i, i+n-1));
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
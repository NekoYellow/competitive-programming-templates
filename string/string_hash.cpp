// https://acm.hdu.edu.cn/showproblem.php?pid=7433
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

class Hash {
  public:
    Hash(const string& s) : n(s.size()), h(n+1), pw(n+1) {
        pw[0][0] = pw[0][1] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2; j++) {
                h[i+1][j] = 1ll * h[i][j]*P[j] % M[j] + s[i];
                pw[i+1][j] = 1ll * pw[i][j]*P[j] % M[j];
            }
        }
    }
    const pii get(int l, int r) { // get hash(s[l..r])
        assert(0 <= l && l <= r && r < n);
        array<int, 2> res;
        for (int j = 0; j < 2; j++) {
            res[j] = h[r+1][j] - 1ll * h[l][j]*pw[r-l+1][j] % M[j];
            res[j] = (res[j] + M[j]) % M[j];
        }
        return {res[0], res[1]};
    }
  private:
    int n, P[2] = {37, 233}, M[2] = {998244353, 1000000007};
    vector<array<int, 2>> pw, h;
};

void solve() { // count how many substrs of t are in cycle(s)
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();

    Hash hs(s+s), ht(t);
    set<pii> pat; // cycle(s)
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
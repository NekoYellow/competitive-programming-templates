// https://loj.ac/p/111
#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
int n, m, p, rk[N<<1], oldrk[N], sa[N<<1], id[N];
// sa[i] := the suffix with rank i; rk[i] := rank of s[i..n] (rk[sa[i]] = i)
void calc_sa(const string& s) {
    n = s.size();
    m = 128; // range
    vector<int> cnt(m+1, 0);
    for (int i = 1; i <= n; i++) cnt[rk[i] = s[i-1]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;
    for (int w = 1; p != n; w <<= 1, m = p) {
        int cur = 0;
        for (int i = n - w + 1; i <= n; i++) id[++cur] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > w) id[++cur] = sa[i] - w;
        cnt.assign(m+1, 0); // memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++) cnt[rk[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[rk[id[i]]]--] = id[i];
        p = 0;
        copy(rk+1, rk+n+1, oldrk+1); // memcpy(oldrk, rk, sizeof(oldrk));
        for (int i = 1; i <= n; i++) {
            if (oldrk[sa[i]] != oldrk[sa[i-1]] || oldrk[sa[i]+w] != oldrk[sa[i-1]+w])
                p++;
            rk[sa[i]] = p;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string s;
    cin >> s;
    int n = s.size();
    calc_sa(s);

    for (int i = 1; i <= n; i++) cout << sa[i] << ' ';
    cout << '\n';

    return 0;
}
/* Luogu-P5829 KMP + LCA */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const char nl = '\n';
const int N = 1e6+10;

char s[N];
int n, fa[23][N], d[N]; // father, depth

void init() {
    fa[0][0] = fa[0][1] = 0; d[0] = 0, d[1] = 1;
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && s[j+1] != s[i]) j = fa[0][j];
        if (s[j+1] == s[i]) j++;
        fa[0][i] = j; d[i] = d[j]+1;
    }
    for (int i = 1; (1<<i) <= n; i++) {
        for (int j = 1; j <= n; j++) {
            fa[i][j] = fa[i-1][fa[i-1][j]];
        }
    }
}

int lca(int p, int q) { // 2-pow lowest-common-ancestor
    if (d[p] < d[q]) swap(p, q);
    for (int i = log2(d[p]-d[q]); i > -1; i--)
        if (d[fa[i][p]] >= d[q])
            p = fa[i][p];
    for (int i = log2(d[p]); i > -1; i--)
        if(fa[i][p] != fa[i][q])
            p = fa[i][p], q = fa[i][q];
    return fa[0][p];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    #endif
    cin >> (s+1);
    n = strlen(s+1);
    init();
    int m;
    cin >> m;
    while (m--) {
        int p, q;
        cin >> p >> q;
        cout << lca(p, q) << nl;
    }
    return 0;
}

/* atcoder abc293D */
#include <bits/stdc++.h>
using namespace std;

// dsu, also known as union-find
const int N = 2e5+10;

int par[N];
int nv[N], ne[N];
int nset;

void init(int n) {
    for (int i = 0; i < n; i++) {
        par[i] = i;
        nv[i] = 1; ne[i] = 0;
    }
    nset = n;
}
int find(int x) {
    if (x == par[x]) return x;
    par[x] = find(par[x]);
    return par[x];
}
void unio(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx != ry) {
        if (nv[rx] < nv[ry]) {
            par[rx] = ry;
            nv[ry] += nv[rx];
            ne[ry] += ne[rx]+1;
        } else {
            par[ry] = rx;
            nv[rx] += nv[ry];
            ne[rx] += ne[ry]+1;
        }
        nset--;
    }
    else {
        ne[rx]++;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    init(n);
    int a, c; char b, d;
    while (m--) {
        cin >> a >> b >> c >> d;
        unio(a-1, c-1);
    }
    int nc = 0;
    for (int i = 0; i < n; i++) {
        nc += nv[i]==ne[i];
    }
    cout << nc << ' ' << nset-nc << '\n';
}

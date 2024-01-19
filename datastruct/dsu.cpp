// https://atcoder.jp/contests/abc293/tasks/abc293_d
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> par, nv, ne;
    int nset;
    void init(int n) {
        par.resize(n); iota(par.begin(), par.end(), 0);
        nv.assign(n, 1);
        ne.assign(n, 0);
        nset = n;
    }
    int find(int x) {
        if (x == par[x]) return x;
        par[x] = find(par[x]);
        return par[x];
    }
    void merge(int x, int y) {
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
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    DSU uf;
    uf.init(n);
    int a, c; char b, d;
    while (m--) {
        cin >> a >> b >> c >> d;
        uf.merge(a-1, c-1);
    }
    int nc = 0;
    for (int i = 0; i < n; i++) {
        nc += uf.nv[i]==uf.ne[i];
    }
    cout << nc << ' ' << uf.nset-nc << '\n';
}

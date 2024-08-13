// https://atcoder.jp/contests/abc293/tasks/abc293_d
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> par, nv, ne;
    int nset;
    DSU(int n) {
        par.resize(n); iota(par.begin(), par.end(), 0);
        nv.assign(n, 1); ne.assign(n, 0);
        nset = n;
    }
    int find(int x) {
        if (x == par[x]) return x;
        return par[x] = find(par[x]);
    }
    void merge(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx != ry) {
            if (nv[rx] < nv[ry]) swap(rx, ry);
            par[ry] = rx;
            nv[rx] += nv[ry]; ne[rx] += ne[ry]+1;
            nset--;
        } else {
            ne[rx]++;
        }
    }
};

namespace Simple {

struct DSU {
    vector<int> par, sz;
    DSU(int n) {
        par.resize(n); iota(par.begin(), par.end(), 0);
        sz.assign(n, 1);
    }
    int find(int x) {
        return x == par[x] ? x : (par[x] = find(par[x]));
    }
    void merge(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;
        if (sz[rx] < sz[ry]) swap(rx, ry);
        par[ry] = rx, sz[rx] += sz[ry];
    }
};



};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    DSU uf(n);
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

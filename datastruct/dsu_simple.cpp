// A simple dsu
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> par, sz;
    DSU(int n) {
        par.resize(n); iota(par.begin(), par.end(), 0);
        sz.assign(n, 1);
    }
    int find(int x) {
        if (x == par[x]) return x;
        return par[x] = find(par[x]);
    }
    void merge(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx != ry) {
            if (sz[rx] < sz[ry]) {
                par[rx] = ry;
                sz[ry] += sz[rx];
            } else {
                par[ry] = rx;
                sz[rx] += sz[ry];
            }
        }
    }
};
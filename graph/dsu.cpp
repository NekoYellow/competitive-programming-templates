/* atcoder abc293D */
#include <bits/stdc++.h>
using namespace std;

// dsu, also known as union-find
vector<int> par, nv, ne; // parent, number of vertices, number of edges
int nset; // nunber of sets (clusters)
void init(int n) {
    par.resize(n); nv.resize(n); ne.resize(n);
    iota(par.begin(), par.end(), 0); // let r[i] = i forall i
    fill(nv.begin(), nv.end(), 1);
    fill(ne.begin(), ne.end(), 0);
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

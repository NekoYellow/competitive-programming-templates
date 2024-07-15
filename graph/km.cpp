// https://www.luogu.com.cn/problem/P6577
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class KM { // Hungarian
  public:
    KM(int _n): n(_n) { e.assign(n+1, vector<ll>(n+1, -inf)); }
    void addedge(int u, int v, int w) { e[u][v] = w; }
    ll km() { // do matching and return the optimal sum of matching
        lx.assign(n+1, 0); ly.assign(n+1, 0);
        couple.assign(n+1, -1);
        for (int i = 1; i <= n; i++) match(i);
        ll sum = 0;
        for (int i = 1; i <= n; i++) sum += e[couple[i]][i];
        return sum;
    }
    vector<int> matching() { return {couple.begin()+1, couple.end()}; }
  private:
    // -inf should be small enough to prevent nonexistent edges from being chosen
    const ll inf = 1e18;
    int n; // #vertices in each set
    vector<vector<ll>> e; // adjacent matrix
    vector<ll> lx, ly; // weight on vertices  $l(u)+l(v) \le w(u, v)$
    vector<int> couple; // couple[y] := optimal matching of y
    void match(int u) {
        vector<int> pre(n+1, 0);
        vector<ll> slack(n+1, inf);
        vector<bool> vis(n+1, 0); // vis[y]: if matching of y is found
        int y = 0;
        couple[y] = u;
        do {
            int ny = 0, x = couple[y];
            ll md = inf;
            vis[y] = 1;
            for (int i = 1; i <= n; i++) {
                if (vis[i]) continue;
                ll d = lx[x]+ly[i] - e[x][i];
                if (d < slack[i]) slack[i] = d, pre[i] = y;
                if (slack[i] < md) md = slack[i], ny = i;
            }
            for (int i = 0; i <= n; i++) {
                if (vis[i]) lx[couple[i]] -= md, ly[i] += md;
                else slack[i] -= md;
            }
            y = ny;
        } while (~couple[y]);
        for (; y; y = pre[y]) couple[y] = couple[pre[y]];
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    KM km(n);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        km.addedge(u, v, w);
    }
    cout << km.km() << '\n';
    for (auto e: km.matching()) cout << e << ' ';
    cout << '\n';
    return 0;
}

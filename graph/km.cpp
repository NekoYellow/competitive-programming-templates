/* 2023 SH Jan C : Bipartite Graph Pairing */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Place {
    int x, y;
} p1[410], p2[410]; // target, current
int n, m; // size of grid, number of vertices

// KM algorithm: find an optimal pairing plan for a bipartite graph
// optimal means maximizing the sum of weights
const int INF = 1e9, MAXN = 500;     // MAXN := number of vertices of each side
int weight[MAXN+7][MAXN+7]; // weights of edges between two sides
int mb[MAXN+7], vb[MAXN+7], ka[MAXN+7], kb[MAXN+7], p[MAXN+7], c[MAXN+7];
int qf, qb, q[MAXN+7];
void bfs(int u) { // find the pairing
    int a, v = 0, vl = 0, d;
    for (int i = 1; i <= m; i++) p[i] = 0, c[i] = INF;
    mb[v] = u;
    do {
        a = mb[v], d = INF, vb[v] = 1;
        for (int b = 1; b <= m; b++)
            if (!vb[b]) {
                if (c[b] > ka[a]+kb[b]-weight[a][b])
                    c[b] = ka[a]+kb[b]-weight[a][b], p[b] = v;
                if (c[b] < d)
                    d = c[b], vl = b;
            }
        for (int b = 0; b <= m; b++) {
            if (vb[b]) ka[mb[b]] -= d, kb[b] += d;
            else c[b] -= d;
        }
        v = vl;
    } while (mb[v]);
    while (v) mb[v] = mb[p[v]], v = p[v];
}

ll km() { // return the maximum weight sum
    for (int i = 1; i <= m; i++)
        mb[i] = ka[i] = kb[i] = 0;
    for (int a = 1; a <= m; a++) {
        for (int b = 1; b <= m; b++) vb[b] = 0;
        bfs(a);
    }
    ll res = 0;
    for (int b = 1; b <= m; b++)
        res += weight[mb[b]][b];
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        getchar(); // '\n'
        m = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j)
                if (getchar() == '#') p1[++m] = {i, j};
            getchar();
        }
        m = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j)
                if (getchar() == '#') p2[++m] = {i, j};
            getchar();
        }
        ++m;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j < m; ++j)
                weight[i][j] = -abs(p1[i].x-p2[j].x)-abs(p1[i].y-p2[j].y);
            weight[i][m] = 0; // to Komorebi
        }
        printf("%lld\n", -km());
    }
    return 0;
}

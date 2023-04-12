/* Edmonds-Karp : O(VE^2) */
/* Cannot remember the origin problem, so the correctness is unknown */
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9, MAXN = 300;
int n, m, graph[MAXN][MAXN], pre[MAXN]; // graph acts also as residual network

int bfs(int s, int t) { // find enlarging path : O(VE)
    int flow[MAXN];
    memset(pre, -1, sizeof(pre));
    flow[s] = INF, pre[s] = 0; // init start vertex
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == t) break; // path found, stop bfs
        for (int i = 1; i <= m; i++) { // bfs every vertex
            if (i != s && graph[u][i] > 0 && pre[i] != -1) {
                pre[i] = u; // record path
                q.push(i);
                flow[i] = min(flow[u], graph[u][i]); // update vertex flow(flux)
            }
        }
    }
    if (pre[t] == -1) return -1; // have not found new enlarging path
    return flow[t]; // return flux of this enlarging path
}

int maxflow(int s, int t) {
    int mf = 0;
    while (1) {
        int flow = bfs(s, t); // find a path and return its flux
        if (flow == -1) break; // no new path
        int cur = t;
        while (cur != s) { // update residual network along the path
            int par = pre[cur];
            graph[par][cur] -= flow; // decrease on the direction
            graph[cur][par] += flow; // increase on the opposite dir
            cur = par;
        }
        mf += flow;
    }
    return mf;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        memset(graph, 0, sizeof(graph));
        for (int i = 0; i < n; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u][v] += w; // duplicate edges may exist
        }
        cout << maxflow(1, m) << endl;
    }
    return 0;
}

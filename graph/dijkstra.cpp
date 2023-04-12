/* hdu-2544 */
#include<bits/stdc++.h>
using namespace std;

const int INF = 1e8, NUM = 1e5;

struct edge {
    int f, t, w; // from, to, weight
    edge(int a, int b, int c): f(a), t(b), w(c) {}
    edge(int a, int b): f(a), t(b), w(1) {}
};
vector<edge> G[NUM]; // adjacency table

struct node { // self-defined pair<int,int>; will be push into a pq
    int id; // index; label
    int dt; // distance to source
    node(int a, int b): id(a), dt(b) {}
    bool operator<(const node &o) const { return dt > o.dt; }
};

int n, m;
int pre[NUM]; // store the previous node

void print_path(int s, int t) { // print the shortest path from s to t
    if (s == t) { cout << s << ' '; return; }
    print_path(s, pre[t]);
    cout << t << ' ';
}

void dijkstra() {
    int s = 1; // source
    int dis[NUM]; // dis[i] = distance from node i to s
    bool vis[NUM]; // visited; vis[i] = true when the shortest path to i has been found
    for (int i = 1; i <= n; i++) { dis[i] = INF; vis[i] = false; }
    dis[s] = 0;
    priority_queue<node> pq;
    pq.push(node(s, dis[s]));
    while(!pq.empty()) {
        auto u = pq.top(); pq.pop();
        if (vis[u.id]) continue;
        vis[u.id] = true;
        for (auto &y: G[u.id]) {
            if (vis[y.t]) continue;
            if (dis[y.t] > u.dt+y.w) {
                dis[y.t] = u.dt+y.w;
                pq.push(node(y.t, dis[y.t]));
                pre[y.t] = u.id; // = y.f
            }
        }
    }
    cout << dis[n] << '\n';
    // print_path(s, n);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    while (cin >> n >> m) {
        if (n==0 && m==0) return 0;
        for (int i = 1; i <= n; i++) G[i].clear();
        while(m--) {
            int a, b, c;
            cin >> a >> b >> c;
            G[a].push_back(edge(a, b, c));
            G[b].push_back(edge(b, a, c));
        }
        dijkstra();
    }
}

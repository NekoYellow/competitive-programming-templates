// https://www.luogu.com.cn/problem/P3379
#include <bits/stdc++.h>
using namespace std;
const char nl = '\n';

struct Edge {
    int to, from, next, LCA;
    Edge(): to(-1), from(-1), next(-1), LCA(-1) {};
    Edge(int u, int v, int n): from(u), to(v), next(n), LCA(-1) {};
};
vector<int> head, qhead;
vector<Edge> edge, qedge;
vector<int> par, visited;
int find(int x) {
    return par[x] == x ? x : (par[x] = find(par[x]));
}
void tarjan(int u) {
    visited[u] = 1;
    for (int i = head[u]; ~i; i = edge[i].next) {
        Edge& e = edge[i];
        if (!visited[e.to]) tarjan(e.to), par[e.to] = u;
    }
    for (int i = qhead[u]; ~i; i = qedge[i].next) {
        Edge& e = qedge[i];
        if (visited[e.to]) qedge[i^1].LCA = e.LCA = find(e.to);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, q, s;
    cin >> n >> q >> s; s--;
    head.assign(n, -1); qhead.assign(n, -1);
    for (int _ = 1; _ < n; _++) {
        int u, v;
        cin >> u >> v; u--, v--;
        edge.push_back(Edge(u, v, head[u]));
        head[u] = edge.size()-1;
        edge.push_back(Edge(v, u, head[v]));
        head[v] = edge.size()-1;
    }
    for (int _ = 0; _ < q; _++) {
        int u, v;
        cin >> u >> v; u--, v--;
        qedge.push_back(Edge(u, v, qhead[u]));
        qhead[u] = qedge.size()-1;
        qedge.push_back(Edge(v, u, qhead[v]));
        qhead[v] = qedge.size()-1;
    }
    par.resize(n); iota(par.begin(), par.end(), 0);
    visited.assign(n, 0);
    tarjan(s);
    for (int i = 0; i < q; i++) {
        cout << qedge[i<<1].LCA + 1 << nl;
    }
    return 0;
}
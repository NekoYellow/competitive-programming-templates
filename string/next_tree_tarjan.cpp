/* Luogu-P5829 KMP + TarjanLCA */
#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
// kmp
int nxt[N];
char s[N];
// dsu
int fa[N];
int get(int x) { return fa[x] == x ? x : fa[x]=get(fa[x]); }
void merge(int x, int y) { if ((x=get(x)) != (y=get(y))) fa[x] = y; }
// graph
bool vis[N];
int head[N], to[2*N], nxt1[2*N], tot;
void add(int u, int v) {
    to[++tot] = v;
    nxt1[tot] = head[u];
    head[u] = tot;
}
// graph2: put the query edges
int head2[N], to2[2*N], nxt2[2*N], num[2*N], tot2;
void add2(int u, int v, int w) {
    to2[++tot2] = v;
    num[tot2] = w;
    nxt2[tot2] = head2[u];
    head2[u] = tot2;
}
// query
int ans[N], x[N], y[N];

void tarjan(int x) {
    vis[x] = true;
    for (int i = head[x]; i; i = nxt1[i])
        if (!vis[to[i]])
            tarjan(to[i]), merge(to[i], x);
    for (int i = head2[x]; i; i = nxt2[i])
        if (vis[to2[i]])
            ans[num[i]] = get(to2[i]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> (s+1);
    int n = strlen(s+1);
    nxt[0] = nxt[1] = 0;
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && s[j+1] != s[i]) j = nxt[j];
        if (s[j+1] == s[i]) j++;
        nxt[i] = j;
    }
    for (int i = 1; i <= n; i++)
        add(nxt[i], i);
    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> x[i] >> y[i];
        add2(x[i], y[i], i);
        add2(y[i], x[i], i);
    }
    tarjan(0);
    for (int i = 1; i <= m; i++)
        cout << ((ans[i]==x[i] || ans[i]==y[i]) ? nxt[ans[i]] : ans[i]) << '\n';
    return 0;
}

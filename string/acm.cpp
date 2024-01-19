// https://www.luogu.com.cn/problem/P5357
/* ac automaton (kmp on trie) */
/* Given a set of pattern strings and a text string, find number of occurences of each pattern in the text. */
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6+10;
const int R = 26; // size of char set

int vis[N], in[N], mp[N];

struct tnode {
    int son[R], fail, flag, ans;
} trie[N];
int pos = 1;
void insert(string s, int num) {
    int u = 1, n = s.size();
    for (int i = 0; i < n; i++) {
        int v = s[i]-'a';
        if (!trie[u].son[v]) trie[u].son[v] = ++pos;
        u = trie[u].son[v];
    }
    if (!trie[u].flag) trie[u].flag = num;
    mp[num] = trie[u].flag;
}

void build() { // form the fail tree
    queue<int> q;
    for (int i = 0; i < R; i++)
        trie[0].son[i] = 1;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int fl = trie[u].fail;
        for (int i = 0; i < R; i++) {
            int v = trie[u].son[i];
            if (!v) {
                trie[u].son[i] = trie[fl].son[i];
                continue;
            }
            trie[v].fail = trie[fl].son[i];
            in[trie[v].fail]++;
            q.push(v);
        }
    }
}
void query(string s) {
    int u = 1, n = s.size();
    for (int i = 0; i < n; i++)
        u = trie[u].son[s[i]-'a'], trie[u].ans++;
}

void topo() {
    queue<int> q;
    for (int i = 1; i <= pos; i++)
        if (!in[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[trie[u].flag] = trie[u].ans;
        int v = trie[u].fail;
        in[v]--;
        trie[v].ans += trie[u].ans;
        if (!in[v]) q.push(v);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        insert(s, i);
    }
    build();
    string t;
    cin >> t;
    query(t);
    topo();
    for (int i = 1; i <= n; i++)
        cout << vis[mp[i]] << '\n';
    return 0;
}

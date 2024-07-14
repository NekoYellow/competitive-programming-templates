// https://www.luogu.com.cn/problem/P5357
#include <bits/stdc++.h>
using namespace std;

class ACA { // AC Automaton, augumented ver.
  public:
    ACA(int _n): n(_n), t(1), cnt(1), pos(1), idx(1) {} // n : #pats
    void insert(const string& s, int id) { // trie.insert  assert(id > 0)
        int u = 0;
        for (auto c: s) {
            c -= 'a';
            if (!t[u][c]) {
                t.push_back(array<int, R>()); cnt.push_back(0); idx.push_back(0);
                t[u][c] = pos++;
            }
            u = t[u][c];
        }
        cnt[u]++; fir[id] = (idx[u] ? idx[u] : (idx[u] = id));
    }
    void build() { // Build the fail tree. Call after all insertions
        deg.resize(t.size()); fail.resize(t.size());
        queue<int> q;
        for (int c = 0; c < R; c++) if (t[0][c]) q.push(t[0][c]);
        while (q.size()) {
            int u = q.front(); q.pop();
            for (int c = 0; c < R; c++) {
                int& v = t[u][c];
                if (!v) v = t[fail[u]][c];
                else fail[v] = t[fail[u]][c], deg[fail[v]]++, q.push(v);
            }
        }
    }
    vector<int> query(const string& s) { // onetime-query of #occurence of each pat in s
        vector<int> acc(pos, 0), ans(n, 0);
        for (int u = 0, i = 0; i < s.size(); i++)
            u = t[u][s[i] - 'a'], acc[u]++;
        // topological traversal
        queue<int> q;
        for (int i = 0; i < pos; i++)
            if (!deg[i]) q.push(i);
        while (q.size()) {
            int u = q.front(); q.pop();
            if (idx[u]) ans[idx[u]-1] = acc[u];
            int v = fail[u];
            acc[v] += acc[u];
            if (!(--deg[v])) q.push(v);
        }
        for (int i = 0; i < n; i++) ans[i] = ans[fir[i+1]-1];
        return ans;
    }

  private:
    int n; static const int R = 26;
    vector<array<int, R>> t; // trie
    vector<int> cnt, idx; // cnt of pat, idx of pat (1-idx)
    vector<int> deg, fail; //in degree, fail trans
    unordered_map<int, int> fir; // first index of a pat (in case of dup)
    int pos;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;
    ACA ac(n);
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        ac.insert(s, i);
    }

    ac.build();
    string t; cin >> t;
    for (auto e: ac.query(t)) cout << e << '\n';

    return 0;
}

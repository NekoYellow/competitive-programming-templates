// https://www.luogu.com.cn/problem/P5357
#include <bits/stdc++.h>
using namespace std;

class ACA { // AC Automaton, augumented ver.
  public:
    ACA(): n(0), t(1), cnt(1), pos(1), idx(1) {}
    void insert(const string& s, int id) { // Insert a pattern to trie.
        int u = 0; assert(id > 0); n = max(n, id);
        for (auto c: s) {
            if (!t[u][c-'a']) {
                t.push_back({}); cnt.push_back(0); idx.push_back(0);
                t[u][c-'a'] = pos++;
            }
            u = t[u][c-'a'];
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
    vector<int> query(const string& s) { // Query for a given text s.
        vector<int> acc(pos, 0), ans(n, 0);
        for (int u = 0, i = 0; i < s.size(); i++)
            u = t[u][s[i] - 'a'], acc[u]++;
        queue<int> q; // topological traversal
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
        return ans; // #occurence of each of the patterns in text
    }
  private:
    static const int R = 26; int n, pos; // #pat, insert position
    vector<array<int, R>> t; // trie
    vector<int> cnt, idx, deg, fail; // .., idx of pat (1-idx), in deg, ..
    unordered_map<int, int> fir; // first index of a pat (in case of dup)
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ACA ac;
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        ac.insert(s, i);
    }

    ac.build();
    string t; cin >> t;
    for (auto e: ac.query(t)) cout << e << '\n';

    return 0;
}

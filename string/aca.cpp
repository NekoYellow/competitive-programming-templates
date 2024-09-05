// https://www.luogu.com.cn/problem/P3808
#include <bits/stdc++.h>
using namespace std;

class ACA { // Trie + fail tr (KMP on Trie)
  public:
    ACA(): t(1), cnt(1), pos(1) {}
    void insert(const string& s) {
        int p = 0;
        for (auto c: s) {
            c -= 'a';
            if (!t[p][c]) {
                t.push_back(array<int, R>()); cnt.push_back(0);
                t[p][c] = pos++;
            }
            p = t[p][c];
        }
        cnt[p]++;
    }
    void build() {
        fail.resize(t.size());
        queue<int> q;
        for (int c = 0; c < R; c++) if (t[0][c]) q.push(t[0][c]);
        while (q.size()) {
            int p = q.front(); q.pop();
            for (int c = 0; c < R; c++) {
                if (!t[p][c]) t[p][c] = t[fail[p]][c];
                else fail[t[p][c]] = t[fail[p]][c], q.push(t[p][c]);
            }
        }
    }
    int query(const string& s) {
        int p = 0, res = 0;
        map<int, bool> vis;
        for (auto c: s) {
            p = t[p][c - 'a'];
            for (int i = p; i && !vis[i]; i = fail[i])
                res += cnt[i], vis[i] = 1;
        }
        return res; // #occ of patterns in s
    }

  private:
    static const int R = 26;
    vector<array<int, R>> t; // trie
    vector<int> cnt, fail;
    int pos;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ACA ac;
    int n; cin >> n;
    while (n--) {
        string s; cin >> s;
        ac.insert(s);
    }

    ac.build();
    string t; cin >> t;
    cout << ac.query(t) << '\n';

    return 0;
}

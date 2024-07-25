// https://codeforces.com/gym/102428/problem/G
#include <bits/stdc++.h>
using namespace std;

class SAM { // link forms a tree, nxt forms a dag
    static const char M = 26, B = 'A';
    int sz, last;
    // i represents a class of substrs sharing the same set of endpos,
    // of length ranging from len[link[i]] + 1 to len[i].
    vector<int> len, link, cnt; // dfs on rev(link) to get cnt of substrs
    vector<array<int, M>> nxt; // can perform matching as if on trie
    void extend(char c) {
        c -= B;
        int cur = sz++;
        len[cur] = len[last] + 1; link[cur] = 0; cnt[cur] = 1;
        int p = last; last = cur;
        for (; p != -1 && !nxt[p][c]; p = link[p]) nxt[p][c] = cur;
        if (p == -1) return;
        int q = nxt[p][c];
        if (len[p] + 1 == len[q]) {
            link[cur] = q;
        } else {
            int clone = sz++;
            len[clone] = len[p] + 1; link[clone] = link[q]; nxt[clone] = nxt[q];
            for (; p != -1 && nxt[p][c] == q; p = link[p]) nxt[p][c] = clone;
            link[q] = link[cur] = clone;
        }
    }
  public:
    SAM(const string &s) : sz(1), last(0) {
        int n = s.size() * 2; // final DAG has <= 2n-1 nodes & 3n-4 edges
        len.resize(n); link.assign(n, -1); nxt.resize(n); cnt.resize(n);
        for (auto c: s) extend(c);
    }
    friend int solve(const SAM &sam, const string &s);
};
// At least how many substrs are needed to concat s?
int solve(const SAM &sam, const string &s) {
    int n = s.size(), ans = 0;
    for (int i = 0; i < n; i++) {
        int p = 0;
        for (int np; i < n; i++, p = np) {
            if (!(np = sam.nxt[p][s[i] - SAM::B])) break;
        }
        if (!p) return -1;
        i--, ans++;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string s; cin >> s;
    SAM sam(s);
    int n; cin >> n;
    while (n--) {
        string t; cin >> t;
        cout << solve(sam, t) << '\n';
    }

    return 0;
}

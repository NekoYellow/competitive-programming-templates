// https://www.luogu.com.cn/problem/P2580
#include <bits/stdc++.h>
using namespace std;

struct Trie {
    static const int R = 26; int pos;
    vector<array<int, R>> t; vector<int> cnt;
    Trie(): t(1), cnt(1), pos(1) {}
    void insert(const string& s) {
        int p = 0;
        for (auto c: s) { c -= 'a';
            if (!t[p][c])
                t.push_back(array<int, R>()), cnt.push_back(0),
                t[p][c] = pos++;
            p = t[p][c];
        }
        cnt[p]++;
    }
    int find(const string& s) {
        int p = 0;
        for (auto c: s) { c -= 'a';
            if (!t[p][c]) return 0; else p = t[p][c];
        }
        return cnt[p]++; // count time mentioned; typically return cnt[p]
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    Trie trie;
    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        trie.insert(s);
    }
    int m;
    cin >> m;
    while (m--) {
        string s;
        cin >> s;
        int cnt = trie.find(s);
        if (cnt == 0) cout << "WRONG\n";
        else if (cnt == 1) cout << "OK\n";
        else cout << "REPEAT\n";
    }

    return 0;
}

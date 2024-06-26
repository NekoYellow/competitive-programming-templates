// https://www.luogu.com.cn/problem/P2580
#include <bits/stdc++.h>
using namespace std;

class Trie {
  public:
    Trie(int n): t(n+1, vector<int>(R)), cnt(n+1, 0), pos(1) {}
    void insert(const string& s) {
        int p = 0;
        for (auto c: s) {
            c -= 'a';
            p = t[p][c] = (t[p][c] ? t[p][c] : pos++);
        }
        cnt[p]++;
    }
    int find(const string& s) {
        int p = 0;
        for (auto c: s) {
            c -= 'a';
            if (!t[p][c]) return 0;
            p = t[p][c];
        }
        return cnt[p]++; // count time mentioned; typically return cnt[p]
    }
  private:
    const int R = 26;
    vector<vector<int>> t;
    vector<int> cnt;
    int pos;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    Trie trie(5e5);
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

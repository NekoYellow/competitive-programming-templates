// https://www.luogu.com.cn/problem/P2580
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+10, R = 26;

int trie[N][R]; // trie stored as array; trie[0] is the root
int num[N]; // number of words with some prefix
int pos = 1; // next position to insert
void insert(const string &s) { // insert a new word to the trie
    int p = 0;
    for (int i = 0; i < s.size(); i++) {
        int n = s[i]-'a';
        if (!trie[p][n]) trie[p][n] = pos++;
        p = trie[p][n];
    }
    num[p]++;
}
int find(const string &s) { // return number of words with the given prefix
    int p = 0;
    for (int i = 0; i < s.size(); i++) {
        int n = s[i]-'a';
        if (!trie[p][n]) return 0;
        p = trie[p][n];
    }
    return num[p]++; // this word is mentioned (typically return num[p];)
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        insert(s);
    }
    int m;
    cin >> m;
    while (m--) {
        string s;
        cin >> s;
        int cnt = find(s);
        if (cnt == 0) cout << "WRONG\n";
        else if (cnt == 1) cout << "OK\n";
        else cout << "REPEAT\n";
    }
    return 0;
}

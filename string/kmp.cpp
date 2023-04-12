/* Luogu-P3375 */
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+10;

string w, t; // word, text
int nxt[N]; // nxt[i] := length of the longest boarder of w[1..i]

int match() {
    int cnt = 0, m = w.size(), n = t.size();
    int p = 0, cur = 0;
    while (cur < n) {
        if (w[p] == t[cur]) p++, cur++;
        else if (p >= 0) p = nxt[p];
        else p = 0, cur++;
        if (p == m) cout << cur-m+1 << '\n', p = nxt[p];
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> t >> w;
    nxt[0] = -1, nxt[1] = 0;
    int p = 0;
    for (int cur = 2; cur <= w.size(); cur++) {
        while (w[p] != w[cur-1] && p >= 0) p = nxt[p];
        nxt[cur] = ++p;
    }
    match();
    for (int i = 1; i <= w.size(); i++) {
        cout << nxt[i] << " \n"[i == w.size()];
    }
}

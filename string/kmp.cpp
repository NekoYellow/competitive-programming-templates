// https://www.luogu.com.cn/problem/P3375
#include <bits/stdc++.h>
using namespace std;

// s[:i] is a boarder of s (len=n) if i<n and s[:i]==s[-i:]
// pi[i] is the length of the longest boarder of s[:i+1]
vector<int> prefix_function(string s) {
    int n = s.length();
    vector<int> pi(n, 0); // pi[0] = 0 by convention
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        pi[i] = j + (s[i] == s[j]);
    }
    return pi;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string txt, pat;
    cin >> txt >> pat;
    int n = txt.size(), m = pat.size();
    vector<int> pi = prefix_function(pat + '#' + txt);

    for (int i = m+1; i < m+n+1; i++) {
        if (pi[i] == m) cout << (i-m+1)-m << '\n';
    }
    for (int i = 0; i < m; i++) {
        cout << pi[i] << " \n"[i == m-1];
    }

    return 0;
}

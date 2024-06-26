// https://www.luogu.com.cn/problem/P3805
/* Find the length of the longest palindrome in a string. */
#include <bits/stdc++.h>
using namespace std;

vector<int> manacher_odd(string& s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n+2);
    for (int i = 1, l = 1, r = 1; i <= n; i++) {
        p[i] = max(0, min(r-i, p[l + (r-i)]));
        while (s[i-p[i]] == s[i+p[i]])
            ++p[i];
        if (i+p[i] > r) l = i-p[i], r = i+p[i];
    }
    return vector<int>(begin(p)+1, end(p)-1);
}

vector<int> manacher(const string& s) {
    string t = "#";
    for (auto c: s)
        t += c, t += '#';
    auto&& res = manacher_odd(t);
    return vector<int>(begin(res)+1, end(res)-1);
}

int main() {
    string s;
    cin >> s;

    auto&& p = manacher(s);
    int ans = 1;
    for (auto e: p)
        ans = max(e, ans);
    cout << ans-1 << '\n';

    return 0;
}

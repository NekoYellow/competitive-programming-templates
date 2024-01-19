// https://www.luogu.com.cn/problem/P3805
/* Find the length of the longest palindrome in a string. */
#include <bits/stdc++.h>
using namespace std;
const int N = 3e7+10;

int p[N]; // p[i] := width of the longest palindrome whose mid is i
string origin, s;

void manacher() {
    int hi = 0, mid;
    for (int i = 1; i < s.size(); i++) {
        if (i < hi)
            p[i] = min(p[(mid<<1)-i], p[mid]+mid-i);
        else
            p[i] = 1;
        while (s[i+p[i]] == s[i-p[i]]) p[i]++;
        if (p[i]+i > hi) {
            hi = i+p[i];
            mid = i;
        }
    }
}

void init() { // change
    s = "!#";
    for (auto c: origin)
        s += c, s += '#';
    s += '$';
}

int main() {
    cin >> origin;
    init();
    memset(p, 0, sizeof(p));
    manacher();
    int ans = 1;
    for (int i = 0; i < s.size(); i++)
        ans = max(p[i], ans);
    cout << ans-1 << endl;
    return 0;
}

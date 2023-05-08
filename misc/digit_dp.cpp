/* https://marsoj.cn/p/P2395 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';

const int N = 11;
int dp[N][10]; // dp[i][j] := number of lunlun numbers whose length is i and start with j
int num[N]; // num[i] := number of lunlun numbers with length <= i

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // pre-calculate dp and num
    for (int j = 0; j < 10; j++) dp[1][j] = 1;
    num[1] = 9;
    for (int i = 2; i < N; i++) {
        for (int j = 0; j < 10; j++) {
            dp[i][j] = dp[i-1][j];
            if (j > 0) dp[i][j] += dp[i-1][j-1];
            if (j < 9) dp[i][j] += dp[i-1][j+1];
            if (j > 0) num[i] += dp[i][j];
        }
        num[i] += num[i-1];
    }

    int k;
    cin >> k;
    int len = 1;
    while (num[len] < k) len++;
    k -= num[len-1];

    int a[len];
    // the highest digit
    for (int j = 1; j < 10; j++) {
        if (dp[len][j] < k) k -= dp[len][j];
        else { a[0] = j; break; }
    }
    // remaining digits
    for (int i = len-1; i > 0; i--) {
        for (int j = max(a[len-i-1]-1, 0); j <= min(a[len-i-1]+1, 9); j++) {
            if (dp[i][j] < k) k -= dp[i][j];
            else { a[len-i] = j; break; }
        }
    }

    ll ans = 0;
    for (auto e: a) {
        ans = ans*10 + e;
    }
    cout << ans << nl;

    return 0;
}

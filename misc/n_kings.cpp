/* LOJ#2153 state-compression dp */
#include <bits/stdc++.h>
using namespace std;
long long sta[1<<10], f[10][1<<10][100];
int n, k, cnt;

int popcount(int x) {
        int pc = 0;
        while (x) pc++, x -= x&-x;
        return pc;
}

void dfs(int mask, int cur) {
    if (cur >= n) { // new valid status
        sta[cnt++] = mask;
        return;
    }
    dfs(mask, cur+1); // not put king on cur
    dfs(mask|(1<<cur), cur+2); // put king on cur
}

bool compatible(int i, int j) {
    if (sta[i] & sta[j]) return false;
    if ((sta[i]<<1) & sta[j]) return false;
    if (sta[i] & (sta[j]<<1)) return false;
    return true;
}

int main() {
    cin >> n >> k;
    cnt = 0;
    dfs(0, 0); // pre-calc all valid status of a row
    for (int i = 0; i < cnt; i++) f[0][i][popcount(sta[i])] = 1;
    for (int r = 1; r < n; r++) // rows
        for (int i = 0; i < cnt; i++)
            for (int j = 0; j < cnt; j++) {
                if (!compatible(i, j)) continue; // invalid transfer
                int pc = popcount(sta[i]);
                for (int u = pc; u <= k; u++) f[r][i][u] += f[r-1][j][u-pc];
            }
    long long ans = 0;
    for (int i = 0; i < cnt; i++) ans += f[n-1][i][k];
    cout << ans << endl;
    return 0;
}

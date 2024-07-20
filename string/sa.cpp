// https://www.luogu.com.cn/problem/P2852 ; https://loj.ac/p/111
#include <bits/stdc++.h>
using namespace std;

using seq = vector<int>;
const int N = 3e4;

int n, m, p, rk[N<<1], oldrk[N], sa[N<<1], id[N]; // 1-indexed

// sa[i] := the suffix with rank i; rk[i] := rank of s[i..n] (rk[sa[i]] = i)
void calc_sa(const seq &s) { // $O(nlogn)$
    n = s.size();
    m = 1e6; // range (128 for string)

    vector<int> cnt(m+1, 0); // counting sort
    for (int i = 1; i <= n; i++) cnt[rk[i] = s[i-1]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;

    for (int w = 1; p != n; w <<= 1, m = p) {
        int cur = 0;
        for (int i = n - w + 1; i <= n; i++) id[++cur] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > w) id[++cur] = sa[i] - w;

        cnt.assign(m+1, 0); // memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++) cnt[rk[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[rk[id[i]]]--] = id[i];

        p = 0;
        copy(rk+1, rk+n+1, oldrk+1); // memcpy(oldrk, rk, sizeof(oldrk));
        for (int i = 1; i <= n; i++) {
            if (oldrk[sa[i]] != oldrk[sa[i-1]] || oldrk[sa[i]+w] != oldrk[sa[i-1]+w])
                p++;
            rk[sa[i]] = p;
        }
    }
}

int height[N]; // h[i] := lcp(sa[i], sa[i-1]) (1-indexed)

void calc_h(const seq &s) { // $O(n)$
    for (int i = 1, k = 0; i <= n; ++i) {
        if (!rk[i]) continue;
        if (k) k--; // using h[rk[i]] >= h[rk[i-1]]-1
        while (s[i-1+k] == s[sa[rk[i]-1]-1+k]) k++;
        height[rk[i]] = k;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, k;
    cin >> n >> k; k--;
    vector<int> a(n);
    for (auto &e: a) cin >> e;

    calc_sa(a);
    calc_h(a);

    int ans = 0;
    deque<int> q; // monoQ: find min in all length-k windows
    for (int i = 1; i <= n; i++) {
        while (q.size() && q.front() <= i-k) q.pop_front(); // out of range
        while (q.size() && height[q.back()] >= height[i])
            q.pop_back(); // stay monotonic (ascending)
        q.push_back(i);
        if (i >= k) ans = max(ans, height[q.front()]); // update answer
    }
    cout << ans << '\n';

    return 0;
}

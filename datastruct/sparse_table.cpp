// https://www.luogu.com.cn/problem/P3865
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5;

// ST: answers RMQ offline (complementary to BIT)
int st[N][32], lg[N]; // sparse table, floor log2

void init(const vector<int> &v) { // $\Theta(n\log n)$
    int len = v.size();
    for (int i = 2; i <= len; i++) lg[i] = lg[i>>1] + 1;
    int l1 = lg[len]+1;
    for (int i = 0; i < len; i++) st[i][0] = v[i];
    for (int j = 1; j < l1; j++) {
        int pj = 1<<(j-1);
        for (int i = 0; i+pj < len; i++)
            st[i][j] = max(st[i][j-1], st[i+pj][j-1]);
    }
}

int query(int l, int r) { // $\Theta(1)$
    int q = lg[r-l+1];
    return max(st[l][q], st[r-(1<<q)+1][q]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &e: a) cin >> e;
    init(a);
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << query(l-1, r-1) << '\n';
    }

    return 0;
}

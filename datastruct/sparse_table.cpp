// https://www.luogu.com.cn/problem/P3865
#include <bits/stdc++.h>
using namespace std;

// ST: answers RMQ offline (complementary to BIT)
template<class T>
struct ST {
    const function<T(T, T)> op; // op(x, x) == x
    vector<array<T, 32>> st;
    vector<int> lg;

    ST(const vector<T> &v, function<T(T, T)> _op) : op(_op) {
        int len = v.size();
        st.resize(len);
        lg.assign(len, 0);
        for (int i = 2; i <= len; i++) lg[i] = lg[i>>1] + 1;
        int l1 = lg[len]+1;
        for (int i = 0; i < len; i++) st[i][0] = v[i];
        for (int j = 1; j < l1; j++) {
            int pj = 1<<(j-1);
            for (int i = 0; i+pj < len; i++)
                st[i][j] = op(st[i][j-1], st[i+pj][j-1]);
        }
    }

    T query(int l, int r) {
        int q = lg[r-l+1];
        return op(st[l][q], st[r-(1<<q)+1][q]);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &e: a) cin >> e;
    ST<int> st(a, [](int x, int y){return max(x, y);});
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << st.query(l-1, r-1) << '\n';
    }

    return 0;
}

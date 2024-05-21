// https://www.luogu.com.cn/problem/P3834
#include<bits/stdc++.h>

using namespace std;

const int inf = 1e9;

struct Node {
    int l, r, k, id;
    bool type;
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    vector<Node> q;
    for (int i = 1; i <= n; i++) {
        q.push_back({0, 0, a[i], i, 0});
    } 
    for (int i = 1, l, r, k; i <= m; i++) {
        cin >> l >> r >> k;
        q.push_back({l, r, k, i, 1});
    }

    // bit-indexed tree; track #elements le than spec val in a[1, r]
    vector<int> c(n + 1);
    auto add = [&](int x, int val) {
        while (x <= n) {
            c[x] += val;
            x += x & -x;
        } 
    };
    auto query = [&](int x) {
        int res = 0;
        while (x) {
            res += c[x];
            x -= x & -x;
        }
        return res;
    };
    
    vector<int> ans(m + 1);
    auto solve = [&](auto self, const vector<Node>& q, int l, int r) -> void {
        if (q.empty()) return;
        
        if (l == r) {
            for (auto v : q) {
                if (v.type) ans[v.id] = l;
            }
            return;
        }
        
        int mid = (l + r) >> 1;
        
        vector<Node> q1, q2;
        for (auto v : q) {
            if (!v.type) {
                if (v.k <= mid) {
                    add(v.id, 1);
                    q1.push_back(v);
                } else {
                    q2.push_back(v);
                }
            } else {
                // #elements le than mid in a[l, r]
                int num = query(v.r) - query(v.l - 1);
                if (v.k <= num) {
                    q1.push_back(v);
                } else {
                    v.k -= num;
                    q2.push_back(v);
                }
            }
        }
        
        for (auto v : q1) {
            if (!v.type) add(v.id, -1);
        }
        self(self, q1, l, mid);
        self(self, q2, mid + 1, r);
    };
    solve(solve, q, -inf, inf);
    
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << "\n"; 
    }
    
    return 0;
}


// https://codeforces.com/gym/102800/problem/M
/* The 14th Jilin Provincial Collegiate Programming Contest, Problem M.
   Solve queries on array to return the xor sum of elements having even
   occurences in a[l..r].
   BIT (Bit-Indexed Tree) is used to track the prefix xor sum of unique
   elements in a.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';

int lowbit(int x) {
    return x & (-x);
}

class BIT {
public:
    BIT(const vector<int>& _a) {
        n = _a.size();
        a.resize(n+1);
        for (int i = 0; i < n; i++) {
            add(i, _a[i]);
        }
    }
    void add(int i, int x) {
        i++;
        while (i <= n) {
            a[i] ^= x;
            i += lowbit(i);
        }
    }
    int query(int i) {
        i++;
        int sum = 0;
        while (i) {
            sum ^= a[i];
            i -= lowbit(i);
        }
        return sum;
    }
private:
    int n;
    vector<int> a;
};

struct node {
    int l, r, i;
};

bool operator<(const node& a, const node& b) {
    return a.r < b.r;
}

void solve() {
    int n, q;
    cin >> n >> q;
    map<int, int> idx;
    vector<int> a(n), pre(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pre[i] = idx.find(a[i])==idx.end() ? -1 : idx[a[i]];
        idx[a[i]] = i;
    }
    vector<node> b(q);
    for (int i = 0; i < q; i++) {
        cin >> b[i].l >> b[i].r;
        b[i].l--, b[i].r--;
        b[i].i = i;
    }
    sort(b.begin(), b.end());

    BIT tree = BIT(a);
    vector<int> ps(n+1, 0);
    for (int i = 0; i < n; i++) {
        ps[i+1] = ps[i]^a[i];
    }
    int p = 0;
    vector<int> ans(q);
    for (auto [l, r, i]: b) {
        for (; p <= r; p++) {
            if (~pre[p]) tree.add(pre[p], a[p]);
        }
        ans[i] = ps[r+1]^ps[l] ^ tree.query(r)^tree.query(l-1);
    }
    for (auto e: ans) {
        cout << e << nl;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}
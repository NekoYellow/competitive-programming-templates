// https://codeforces.com/gym/105222/problem/G
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';

template <class T> // T := int or ll
class Trie01 {
  public:
    Trie01(): t(1), v(1), pos(1) {}
    void insert(T s, int idx) {
        int p = 0;
        for (int i = H; i > -1; i--) {
            int c = (s >> i) & 1;
            if (!t[p][c]) {
                t.push_back({0, 0}); v.push_back(0);
                t[p][c] = pos++;
            }
            p = t[p][c];
        }
        v[p] = idx;
    }
    T findmin(T s, int& idx) { // find min(s^e for all e in trie)
        int p = 0;
        T res = 0;
        for (int i = H; i > -1; i--) {
            int c = (s >> i) & 1;
            if (t[p][c]) p = t[p][c];
            else res |= ((T)1 << i), p = t[p][1-c];
        }
        idx = v[p];
        return res;
    }
    T findmax(T s, int& idx) { // find max(s^e for all e in trie)
        int p = 0;
        T res = 0;
        for (int i = H; i > -1; i--) {
            int c = (s >> i) & 1;
            if (t[p][1-c]) res |= ((T)1 << i), p = t[p][1-c];
            else p = t[p][c];
        }
        idx = v[p];
        return res;
    }
  private:
    int H = 30; // or 62 if ll
    vector<array<int, 2>> t;
    vector<int> v;
    int pos;
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
    
    int n, q;
    cin >> n >> q;
    vector<int> v(n+1);
    Trie01<int> t;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        t.insert(v[i], i);
    }

    auto bs = [&](int l, int r, int a, int b) {
        bool sl = ((v[l]^a) > b), sr = ((v[r]^a) > b);
        while (r-l > 1) {
            int mid = (l+r)/2;
            if ((v[mid]^a) == b) {
                cout << (mid-1 ? mid-1 : mid) << nl;
                return;
            }
            else if (((v[mid]^a) > b) == sl) l = mid;
            else r = mid;
        }
        cout << l << nl;
    };

    while (q--) {
        int a, b;
        cin >> a >> b;
        int imn, imx;
        int mn = t.findmin(a, imn), mx = t.findmax(a, imx);

        if (mn > b || mx < b) {
            cout << -1 << nl;
            continue;
        }
        if (mn == b) {
            cout << (imn-1 ? imn-1 : imn) << nl;
            continue;
        }
        if (mx == b) {
            cout << (imx-1 ? imx-1 : imx) << nl;
            continue;
        }

        int l = min(imn, imx), r = max(imn, imx);
        bs(l, r, a, b);
    }

    return 0;
}
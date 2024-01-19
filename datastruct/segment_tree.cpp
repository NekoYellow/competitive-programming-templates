/* cf 1904D : judge if a can be transfered into b
   by several a[l:r] <- max(a[l:r]) operations */
#include "bits/stdc++.h"
using namespace std;
#define ll long long

template <typename T>
struct ST {

    int n;
    int bstart, stsize;
    vector<T> st, up;

    /* TO FILL IN */
    const T zero = 0;
    const T noup = -1;
    T op(T a, T b) {
        return max(a, b);
    }

    void pushdown(int c, ll cmin, ll cmax) {
        if (up[c] == noup) return;
        st[c] = up[c];
        if (c < bstart) {
            up[c * 2 + 1] = up[c];
            up[c * 2 + 2] = up[c];
        }
        up[c] = noup;
    }

    ST(int _n) {
        n = _n;
        bstart = 1;
        while (bstart < n) bstart *= 2;
        stsize = bstart * 2 - 1;
        bstart--;

        st.resize(stsize, zero);
        up.resize(stsize, noup);
    }
    
    void update(int c, int cmin, int cmax, int minb, int maxb, T v) {
        pushdown(c, cmin, cmax);
        if (cmin >= minb && cmax <= maxb) {
            up[c] = v;
            pushdown(c, cmin, cmax);
            return;
        }
        if (cmin > maxb || cmax < minb) return;
        update(c * 2 + 1, cmin, (cmin + cmax) / 2, minb, maxb, v);
        update(c * 2 + 2, 1 + (cmin + cmax) / 2, cmax, minb, maxb, v);
        st[c] = op(st[c * 2 + 1], st[c * 2 + 2]);
    }

    void update(int lo, int hi, T v) {
        update(0, 0, bstart, lo, hi, v);
    }

    T query(int c, int cmin, int cmax, int minb, int maxb) {
        pushdown(c, cmin, cmax);
        if (cmin >= minb && cmax <= maxb) return st[c];
        if (cmin > maxb || cmax < minb) return zero;
        return op(query(c * 2 + 1, cmin, (cmin + cmax) / 2, minb, maxb),
                        query(c * 2 + 2, 1 + (cmin + cmax) / 2, cmax, minb, maxb));
    }

    T query(int lo, int hi) {
        return query(0, 0, bstart, lo, hi);
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t; cin >> t;
    while (t--) {

        int n; cin >> n;

        vector<int> a(n);
        for (int &i : a) {
            cin >> i;
            i--;
        }

        vector<int> b(n);
        for (int &i : b) {
            cin >> i;
            i--;
        }

        vector<vector<int>> ap(n), bp(n);
        set<int> bless, amore;
        ST<int> helper(n + 5);

        bless.insert(-1);
        amore.insert(-1);
        bless.insert(n);
        amore.insert(n);

        for (int i = 0; i < n; i++) {
            ap[a[i]].push_back(i);
            bp[b[i]].push_back(i);
            helper.update(i, i, a[i]);
            amore.insert(i);
        }

        for (int i = 0; i < n; i++) {
            for (int x : ap[i]) {
                amore.erase(x);
            }

            for (int x : ap[i]) {

                int nit = min(*amore.lower_bound(x), *bless.lower_bound(x));
                int pit = max(*(--amore.lower_bound(x)), *(--bless.lower_bound(x)));

                helper.update(pit + 1, nit - 1, i);

            }

            for (int x : bp[i]) {
                bless.insert(x);
            }
        }

        int ok = 1;
        for (int i = 0; i < n; i++) {
            if (helper.query(i, i) != b[i]) {
                ok = 0;
            }
        }

        cout << (ok ? "YES\n" : "NO\n");

    }
    
}

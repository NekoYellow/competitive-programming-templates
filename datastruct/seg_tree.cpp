// simple segmentree: point modification & range query
#include <bits/stdc++.h>
using namespace std;

template<class T>
class SegTree {
  private:
    int n;
    vector<T> t;

    /* TO FILL IN */
    const T e = 0; // identity of op
    T op(T a, T b) {
        return max(a, b);
    }

    void update(int pos, int pl, int pr, int i, T val) {
        if (pl == pr) {
            t[pos] = val;
            return;
        }
        int m = (pl + pr)/2;
        if (i <= m) update(pos*2, pl, m, i, val);
        else update(pos*2+1, m+1, pr, i, val);
        t[pos] = op(t[pos*2], t[pos*2+1]);
    }
    T query(int pos, int pl, int pr, int l, int r) {
        if (l <= pl && pr <= r) {
            return t[pos];
        }
        int m = (pl + pr)/2;
        T res = e;
        if (l <= m) res = op(res, query(pos*2, pl, m, l, r));
        if (r > m) res = op(res, query(pos*2+1, m+1, pr, l, r));
        return res;
    }

  public:
    SegTree(int _n) : n(_n), t(_n*4, e) {}
    void update(int i, T val) {
        return update(1, 0, n, i, val);
    }
    T query(int l, int r) {
        return query(1, 0, n, l, r);
    }
};
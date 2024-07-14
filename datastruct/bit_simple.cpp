// A simple, 1-indexed BIT
#include <bits/stdc++.h>
using namespace std;

template <class T>
struct BIT {
    int n;
    vector<T> t;

    BIT(int _n): n(_n) { t.assign(n+1, 0); }
    void add(int x, T v) {
        while (x <= n) t[x] += v, x += x & -x;
    }
    T query(int x) {
        T r = 0;
        while (x) r += t[x], x -= x & -x;
        return r;
    }
};

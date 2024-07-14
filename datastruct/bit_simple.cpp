// A simple, 1-indexed BIT
#include <bits/stdc++.h>
using namespace std;

struct BIT {
    int n;
    vector<int> t;

    BIT(int _n): n(_n) { t.assign(n+1, 0); }
    void add(int x, int v) {
        while (x <= n) t[x] += v, x += x & -x;
    }
    int query(int x) {
        int r = 0;
        while (x) r += t[x], x -= x & -x;
        return r;
    }
};
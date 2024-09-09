// https://www.luogu.com.cn/problem/P3812
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

// greedy
ull p[64];

void insert(ull x) {
    for (int i = 63; ~i; i--) {
        if (!(x >> i)) continue;
        if (!p[i]) {
            p[i] = x;
            break;
        }
        x ^= p[i];
    }
}

template<class T> struct Basis { // Gaussian Eli
    vector<T> a;
    void insert(T x) { a.push_back(x); }
    void calc() {
        int sz = a.size(), r = 0, w = log2(numeric_limits<T>::max());
        for (int c = w-1; r < sz && c > -1; c--) {
            for (int i = r; i < sz; i++) {
                if ((a[i] >> c) & 1) {
                    swap(a[r], a[i]);
                    break;
                }
            }
            if (!((a[r] >> c) & 1)) continue;
            for (int i = 0; i < sz; i++) {
                if (i == r) continue;
                if ((a[i] >> c) & 1) a[i] ^= a[r];
            }
            r++;
        }
        a.resize(r);
    }
    T mx() {
        T res = 0;
        for (auto e: a) res ^= e;
        return res;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    Basis<ull> b;
    for (int i = 0; i < n; i++) {
        ull a;
        cin >> a;
        b.insert(a);
    }

    b.calc();
    cout << b.mx() << '\n';

    return 0;
}
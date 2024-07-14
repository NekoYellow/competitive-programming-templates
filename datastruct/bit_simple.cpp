// A simple, 1-indexed BIT
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; // cin >> n;
    vector<int> c(n+1, 0);
    auto add = [&](int x, int val) {
        while (x <= n) c[x] += val, x += x & -x;
    };
    auto query = [&](int x) {
        int res = 0;
        while (x) res += c[x], x -= x & -x;
        return res;
    };
}
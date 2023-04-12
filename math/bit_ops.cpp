/* A few useful bit operations */
#include <bits/stdc++.h>
using namespace std;

// count number of digits in x's bin repr
int lg(int x) {
    int d = 0;
    while (x) d++, x>>=1;
    return d ? d-1: d;
}
// the highest 1: 1<<(lg(x))

// count number of 1's in x's bin repr (Hamming weight)
int popcount(int x) {
    int cnt = 0;
    while (x) {
        cnt++;
        x -= x & -x;
    }
    return cnt;
}

int main() {
    // enumerate all numbers in [0, n] in ascending order of Hamming weight
    int n = 100;
    for (int i = 0; (1<<i)-1 <= n; i++) {
        for (int x = (1<<i)-1, t; x <= n; t = x+(x&-x), x = x ? (t|((((t&-t)/(x&-x))>>1)-1)) : (n+1)) {
            // cout << x << ' ';
        }
    }
}

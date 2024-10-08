// https://loj.ac/p/2605 Solve ax = 1 (mod b).
#include <bits/stdc++.h>
using namespace std;

// Solving ax + by = gcd(a, b)
void exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}

int main() {
    int a, b;
    cin >> a >> b;
    int x, y;
    exgcd(a, b, x, y);
    x = (x % b + b) % b;
    cout << x << '\n';
    return 0;
}

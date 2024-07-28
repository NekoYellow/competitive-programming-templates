#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
const int M = 998'244'353, G = 3, Gi = 332'748'118;
int rev[N << 2], f[N << 2], g[N << 2];

int qpow(int a, int n) {
    int res = 1;
    for (; n; a = 1ll * a * a % M, n >>= 1)
        if (n & 1) res = 1ll * res * a % M;
    return res;
}
// do ntt on a[0..lim-1]
void NTT(int *a, int lim, int type) { // type = 1: FFT; type = -1: iFFT
    for (int i = 0; i < lim; i++) if(i < rev[i]) swap(a[i], a[rev[i]]);
    for (int mid = 1; mid < lim; mid <<= 1) {
        int wn = qpow(type == 1 ? G : Gi, (M - 1) / (mid << 1));
        for (int i = 0; i < lim; i += (mid << 1)) {
            int w = 1;
            for (int j = 0; j < mid; j++, w = 1ll * w * wn % M) {
                int x = a[i + j], y = 1ll * w * a[i + mid + j] % M;
                a[i + j] = (x + y) % M;
                a[i + mid + j] = (x - y + M) % M;
            }
        }
    }
    if (type == 1) return;
    int limi = qpow(lim, M - 2);
    for (int i = 0; i < lim; i++) a[i] = 1ll * a[i] * limi % M;
}

// Example: for all k, count number of pairs of elements in input array a
// whose value diff is k via convolution (become mult after FourierT)
signed main() {
    int n; cin >> n;
    int m = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        f[x]++; m = max(m, x);
    }
    for (int i = 0; i <= m; i++) g[i] = f[m-i]; // ans = f * g
    int lim = 1; for (; lim <= 2*m; lim <<= 1) ;
    for (int i = 0; i < lim; i++)
        rev[i] = (rev[i>>1] >> 1) | (1ll * (i&1) * (lim>>1));
    NTT(f, lim, 1); NTT(g, lim, 1);
    for (int i = 0; i < lim; i++) f[i] = 1ll * f[i] * g[i] % M;
    NTT(f, lim, -1);
    // now f[m-k] := #pairs (i,j) s.t. a[i]-a[j]==k
    for (int i = m; i > 0; i--) cout << f[i] << ' '; cout << '\n';
}
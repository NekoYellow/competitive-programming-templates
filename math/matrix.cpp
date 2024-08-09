// https://www.luogu.com.cn/problem/P4783
// mult, power, inv of matrix
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 401, M = 1e9 + 7;

int qpow(int a, ll n) {
    int res = 1;
    for (; n; n >>= 1, a = 1ll * a*a % M) {
        if (n & 1) res = 1ll * res*a % M;
    }
    return res;
}

struct Mat {
    int n, a[N][N];
    Mat(int n=N) : n(n) { memset(a, 0, sizeof(a)); }
    int *operator[](int i) { return a[i]; }
    const int *operator[](int i) const { return a[i]; }
};

Mat operator+(const Mat &a, const Mat &b) {
    assert(a.n == b.n);
    Mat c(a.n);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            c[i][j] = (a[i][j] + b[i][j]) % M;
        }
    }
    return c;
}

Mat operator-(const Mat &a, const Mat &b) {
    assert(a.n == b.n);
    Mat c(a.n);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            c[i][j] = (a[i][j] - b[i][j] + M) % M;
        }
    }
    return c;
}

Mat operator*(const Mat &a, const Mat &b) {
    assert(a.n == b.n);
    Mat c(a.n);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                c[i][j] = (c[i][j] + 1ll * a[i][k] * b[k][j] % M) % M;
            }
        }
    }
    return c;
}

Mat I(int n) {
    Mat res(n);
    for (int i = 0; i < n; i++)
        res[i][i] = 1;
    return res;
}

Mat mat_pow(Mat a, ll n) {
    Mat res = I(a.n);
    for (; n; a = a*a, n >>= 1) {
        if (n & 1) res = res*a;
    }
    return res;
}

// const int N = 401, M = 1e9 + 7;
int A[N][N<<1]; bool singular;

void row_minus(int r1, int r2, int k) {
    for (int i = 0; i < N<<1; i++)
        A[r1][i] = (A[r1][i] - 1ll * A[r2][i] * k % M + M) % M;
}
void row_mult(int r, ll k) {
    for (int i = 0; i < N<<1; i++) A[r][i] = (1ll * A[r][i] * k) % M;
}
void row_swap(int r1, int r2) {
    for (int i = 0; i < N<<1; i++) swap(A[r1][i], A[r2][i]);
}

Mat mat_inv(const Mat &x) { // Gauss-Jordan
    memset(A, 0, sizeof(A));
    int n = x.n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = x[i][j];
            A[i][n + j] = (i == j);
        }
    }
    for (int i = 0; i < n; i++) {
        if (!A[i][i]) {
            for (int j = i + 1; j < n; j++) {
                if (A[j][i]) {
                    row_swap(i, j);
                    break;
                }
            }
        }
        row_mult(i, qpow(A[i][i], M-2));
        for (int j = i+1; j < n; j++) {
            row_minus(j, i, A[j][i]);
        }
    }
    for (int i = n-1; i > -1; i--) {
        for (int j = i-1; j > -1; j--) {
            row_minus(j, i, A[j][i]);
        }
    }
    Mat res; singular = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            singular |= (i == j && A[i][j] != 1) | (i != j && A[i][j]);
            res[i][j] = A[i][n+j];
        }
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    Mat a(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    Mat ai = mat_inv(a);
    if (singular) {
        cout << "No Solution\n";
        return 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << ai[i][j] << " \n"[j == n-1];
        }
    }

    return 0;
}
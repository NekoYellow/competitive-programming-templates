"This techique could be used in some sequence problems."

MOD = int(1e9+7)

def I(n: int):
    return [[1 if j==i else 0 for j in range(n)] for i in range(n)]

def mat_mul(A, B):
    m, p, n = len(A), len(A[0]), len(B[0])
    if p != len(B): return [[]]
    res = [[0]*n for _ in range(m)] # [[0]*n]*m would raise bug (all rows refer to a single list)
    for i in range(m):
        for k in range(p):
            r = A[i][k]
            for j in range(n):
                res[i][j] += r * B[k][j]
                res[i][j] %= MOD
    return res

def mat_pow(A, n):
    if len(A) != len(A[0]): return [[]]
    res = I(len(A))
    while n:
        if n & 1: res = mat_mul(A, res)
        A = mat_mul(A, A)
        n >>= 1
    return res

def fibonacci(n):
    """Return the nth number of the fibonacci sequence (1, 1, 2, 3, 5, ...).
    Run in O(logn) time."""
    assert n > 0
    return mat_mul([[1, 0]], mat_pow([[1, 1], [1, 0]], n-1))[0][0]

def fib(n):
    """Return the nth number of the fibonacci sequence (1, 1, 2, 3, 5, ...).
    Run in O(logn) time."""
    assert n > 0
    A = [[1, 1], [1, 0]]
    res = [[1], [0]]
    n -= 1
    while n:
        if n & 1: res = mat_mul(A, res)
        A = mat_mul(A, A)
        n >>= 1
    return res[0][0]


if __name__ == '__main__':
    # test
    for i in range(1, 16):
        print(fibonacci(i), fib(i))

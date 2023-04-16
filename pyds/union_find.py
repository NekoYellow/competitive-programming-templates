class UnionFind:
    def __init__(self, n):
        self.par = {i:i for i in range(n)}
        self.sz = {i:1 for i in range(n)}

    def find(self, x):
        root = x
        while self.par[root] != root:
            root = self.par[root]
        while x != root: # path compression
            x, self.par[x] = self.par[x], root
        return root
    
    def union(self, x, y):
        rx, ry = self.find(x), self.find(y)
        if rx == ry: return
        if self.sz[rx] < self.sz[ry]:
            self.par[rx] = ry
            self.sz[ry] += self.sz[rx]
        else:
            self.par[ry] = rx
            self.sz[rx] += self.sz[ry]

    def isconnected(self, x, y):
        return self.find(x) == self.find(y)


if __name__ == '__main__':
    # test
    uf = UnionFind(10)
    print(uf.isconnected(1, 2))
    uf.union(1, 2)
    uf.union(2, 3)
    print(uf.isconnected(1, 3))

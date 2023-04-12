class Graph:
    def __init__(self, n=100, use_mat=True, edges=[]):
        if use_mat:
            self.G = [[-1]*n for _ in range(n)]
        else:
            self.G = [[] for _ in range(n)]
        self.vs = set()
        self.indeg = [0]*n
        self.mat = use_mat
        self.n = n

    def put_edge(self, u, v, w=1):
        self.vs.add(u)
        self.vs.add(v)
        self.indeg[v] += 1
        if self.mat:
            self.G[u][v] = w
        else:
            self.G[u].append(v) # not weighted
    
    def neighbors(self, u):
        if self.mat:
            for v in range(self.n):
                if self.G[u][v] != -1:
                    yield v
        else:
            for v in self.G[u]:
                yield v
    
    def get_path(self, s, e):
        vis = [0]*self.n
        par = [-1]*self.n
        def dfs(u):
            vis[u] = 1
            for v in self.neighbors(u):
                if not vis[v]:
                    par[v] = u
                    dfs(v)
        dfs(s)
        if not vis[e]: return None # no path found
        path = []
        p = e
        while p != s:
            path.append(p)
            p = par[p]
        path.append(s)
        return list(reversed(path))

    def bfs(self, s, e): # same effect as get_path
        vis = [0]*self.n
        par = [-1]*self.n
        q = [s]
        while q:
            u = q.pop(0)
            vis[u] = 1
            for v in self.neighbors(u):
                if not vis[v]:
                    par[v] = u
                    q.append(v)
        if not vis[e]: return None # no path found
        path = []
        p = e
        while p != s:
            path.append(p)
            p = par[p]
        path.append(s)
        return list(reversed(path))
    
    def has_path(self, path):
        if len(path) < 2:
            return True
        i = 1
        while i < len(path):
            if path[i] not in self.neighbors(path[i-1]):
                return False
            i += 1
        return True
    
    def has_cycle(self): # detect cycle via topological sort
        ind = {v:ind for ind,v in zip(self.indeg,range(self.n)) if v in self.vs}
        q = []
        for v, i in ind.items():
            if not i:
                q.append(v)
        cnt = 0 # number of vertices that are not in a cycle
        while q:
            u = q.pop(0)
            cnt += 1
            for v in self.neighbors(u):
                ind[v] -= 1
                if not ind[v]:
                    q.append(v)
        return cnt < len(self.vs)
      
      
if __name__ == '__main__':
    # test
    G = Graph()
    G.put_edge(1, 2)
    G.put_edge(2, 3)
    G.put_edge(3, 5)
    G.put_edge(2, 6)
    G.put_edge(6, 8)
    
    print(G.get_path(1, 8))
    
    print(G.bfs(1, 8), G.bfs(1, 7))
    
    print(G.has_path([1,2,6,8]), G.has_path([1,2,5,8]))
    
    print(G.has_cycle())
    
    G.put_edge(5, 1)
    print(G.has_cycle())

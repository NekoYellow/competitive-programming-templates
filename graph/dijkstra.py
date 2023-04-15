"LC 6336"
from math import inf
from heapq import heappush, heappop

class Graph:
    def __init__(self, n, edges):
        self.n = n
        self.G = {}
        for edge in edges:
            self.addEdge(edge)

    def addEdge(self, edge):
        u, v, w = edge
        if u not in self.G:
            self.G[u] = set()
        self.G[u].add((v, w))

    def shortestPath(self, src, dst):
        "Return distance of the shortest path from `src` to `dst`."
        dist = [inf] * self.n # dist[u]:= distance of the shortest path from src to u
        dist[src] = 0
        pq = [(dist[src], src)] # min heap
        while pq: # span a shortest-path tree from src
            du, u = heappop(pq) # u:= vertex with the min dist (du) in tree
            if du > dist[u]: continue
            if u == dst: return du
            for v, w in self.G.get(u, []):
                if dist[u] + w < dist[v]: # shorter path found
                    dist[v] = dist[u] + w
                    heappush(pq, (dist[v], v)) # v is now in tree
        return dist[dst] if dist[dst] != inf else -1

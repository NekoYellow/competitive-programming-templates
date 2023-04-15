from math import inf
from heapq import heappush, heappop
from typing import List

class Graph:
    def __init__(self, n: int, edges: List[List[int]]):
        self.n = n
        self.G = [[0]*n for _ in range(n)]
        for edge in edges:
            self.addEdge(edge)

    def addEdge(self, edge: List[int]) -> None:
        u, v, w = edge
        self.G[u][v] = w

    def dijkstra(self, src: int, dst: int) -> int:
        "Return distance of the shortest path from `src` to `dst`."
        dist = [inf] * self.n # dist[u]:= distance of the shortest path from src to u
        dist[src] = 0
        pq = [(dist[src], src)] # min heap
        while pq: # span a shortest-path tree from src
            du, u = heappop(pq) # u:= vertex with the min dist (du) in tree
            if du > dist[u]: continue
            if u == dst: return du
            for v in range(self.n):
                if not self.G[u][v]: continue # no edge from u to v
                if dist[u] + self.G[u][v] < dist[v]: # shorter path found
                    dist[v] = dist[u] + self.G[u][v]
                    heappush(pq, (dist[v], v)) # v is now in tree
        return dist[dst] if dist[dst] != inf else -1

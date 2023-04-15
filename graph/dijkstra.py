from math import inf
from heapq import heappush, heappop

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
            _, u = heappop(pq) # vertex with the min dist in tree
            for v in range(self.n):
                if not self.G[u][v]: continue # no edge from u to v
                if dist[u] + self.G[u][v] < dist[v]: # shorter path found
                    dist[v] = dist[u] + self.G[u][v]
                    heappush(pq, (dist[v], v)) # v is now in tree
        return dist[dst] if dist[dst] != inf else -1

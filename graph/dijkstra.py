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
        dist = [inf] * self.n
        dist[src] = 0
        pq = [(dist[src], src)]
        while pq:
            _, u = heappop(pq)
            for v in range(self.n):
                if not self.G[u][v]: continue
                if dist[u] + self.G[u][v] < dist[v]:
                    dist[v] = dist[u] + self.G[u][v]
                    heappush(pq, (dist[v], v))
        return dist[dst] if dist[dst] != inf else -1

class Heap:
    def __init__(self, data=[], key=lambda v: v, ismax=True):
        self._h = data
        self._N = len(data)
        self._key, self._max = key, ismax
        if self._N > 1:
            for k in range(self._N>>1, 0, -1): 
                self._sink(k)

    def empty(self):
        return self._N == 0

    def push(self, val):
        self._h.append(val)
        self._N += 1
        self._swim(self._N)

    def pop(self):
        last = self._h.pop()
        self._N -= 1
        if self._h:
            ret = self._h[0]
            self._h[0] = last
            self._sink(1)
            return ret
        return last

    def top(self):
        return self._h[0]

    def _swim(self, k):
        while k > 1:
            if self._less(k>>1, k):
                self._exch(k>>1, k)
            k >>= 1

    def _sink(self, k):
        while k << 1 <= self._N:
            j = k << 1
            if j < self._N and self._less(j, j+1):
                j += 1
            if not self._less(k, j):
                return
            self._exch(k, j)
            k = j

    def _less(self, i, j):
        if self._max:
            return self._key(self._h[i-1]) < self._key(self._h[j-1])
        else:
            return self._key(self._h[i-1]) > self._key(self._h[j-1])
    
    def _exch(self, i, j):
        self._h[i-1], self._h[j-1] = self._h[j-1], self._h[i-1]
    
    def __len__(self):
        return len(self._h)
    
    def __str__(self):
        return str(self._h) + ', ' + ("maxheap" if self._max else "minheap")

    def __bool__(self):
        return self._N != 0
      

if __name__ == '__main__':
    # test
    a = [1, 4, 2, 8, 5, 7]
    pq = Heap(ismax=False)
    for e in a:
        pq.push(e)
    sorted_a = []
    while not pq.empty():
        sorted_a.append(pq.pop())
    print(sorted_a)

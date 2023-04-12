class Node:  # struct of segment tree node
    def __init__(self, v, l, r):
        self.v = v
        self.l, self.r = l, r
        self.add = 0 # for lazy-tagging
        self.child = [None, None]

    def __str__(self):
        return f"({self.v})[{self.l},{self.r}] " + (str(self.child[0]) if self.child[0] else '') + (str(self.child[1]) if self.child[1] else '')

def push_up(node):
    node.v = node.child[0].v + node.child[1].v

def push_down(node):
    if node.add:
        add = node.add
        mid = (node.l+node.r)//2
        node.child[0].add += add
        node.child[1].add += add
        node.child[0].v += add*(mid-node.l+1)
        node.child[1].v += add*(node.r-mid)
        node.add = 0 # cancel tagging

def build(l, r): # build a segment tree, return its root
    root = Node(0, l, r)
    if l == r: return root
    mid = (l+r)//2
    root.child = [build(l, mid), build(mid+1, r)]
    return root

def update(node, l, r, a):
    assert node.l <= l and r <= node.r
    if l == node.l and node.r == r:
        node.v += a*(r-l+1)
        node.add += a # lazy-tagging
        return
    push_down(node)
    mid = (node.l+node.r)//2
    if l <= mid: update(node.child[0], l, mid, a)
    if r > mid: update(node.child[1], mid+1, r, a)
    push_up(node)

def query(node, l, r):
    if l <= node.l and node.r <= r: return node.v
    push_down(node)
    mid = (node.l+node.r)//2
    res = 0
    if l <= mid: res += query(node.child[0], l, r)
    if r > mid: res += query(node.child[1], l, r)
    return res


if __name__ == '__main__':
    # test
    tree = build(1, 8)
    print(tree)
    update(tree, 1, 8, 5)
    print(query(tree, 1, 8)) # 40
    print(tree)
    update(tree, 1, 4, 3)
    print(query(tree, 1, 8)) # 52
    print(tree)
    print(query(tree, 1, 5)) # 37

class BNode:
    """Binary Search Tree Node"""
    def __init__(self, v=None, l=None, r=None):
        self.v = v
        self.l, self.r = l, r
        
class BST:
    """Binary Search Tree"""
    def __init__(self, data=[]) -> None:
        self.root = None
        self.size = 0
        for v in data:
            self.insert(v)
    
    def insert(self, v):
        if not self.root:
            self.root = BNode(v)
            self.size = 1
            return
        p = self.root
        while True:
            if v < p.v:
                if not p.l:
                    p.l = BNode(v)
                    self.size += 1
                    return
                p = p.l
            elif v > p.v:
                if not p.r:
                    p.r = BNode(v)
                    self.size += 1
                    return
                p = p.r
            else:
                return

    def inorder(self):
        a = []
        self.getInorder(self.root, a)
        return a
    
    def getInorder(self, p, a):
        if not p: return
        self.getInorder(p.l, a)
        a.append(p.v)
        self.getInorder(p.r, a)

    def min(self):
        if not self.root: return None
        p = self.root
        while p.l: p = p.l
        return p.v
    
    def max(self):
        if not self.root: return None
        p = self.root
        while p.r: p = p.r
        return p.v

    def __len__(self):
        return self.size

    def __str__(self):
        return str(self.inorder())


if __name__ == '__main__':
    # test
    bst = BST([1,4,2,8,5,7])
    print(bst.min(), bst.max())
    print(bst)

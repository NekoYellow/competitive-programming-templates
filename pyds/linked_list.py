class LNode:
    """Linked List Node"""
    def __init__(self, v=None, p=None, n=None):
        self.value = v
        self.prev, self.next = p, n

class LinkedList:
    """Singly Linked List"""
    def __init__(self, data=[]):
        self.head = None
        self.size = 0
        for v in data:
            self.insert(v)
    
    def insert(self, v):
        if not self.head:
            self.head = LNode(v)
            self.size = 1
            return
        p = self.head
        while p.next: p = p.next
        p.next = LNode(v)
        self.size += 1
    
    def delete(self, v):
        if self.head.value == v:
            self.head = self.head.next
            self.size -= 1
            return
        p = self.head, c = self.head.next
        while c and c.value != v:
            p = c
            c = c.next
        if not c: return # not found
        p.next = c.next
        self.size -= 1

    def __len__(self):
        return self.size

    def __str__(self):
        r = []
        p = self.head
        while p:
            r += [p.value]
            p = p.next
        return str(r)

class DoublyLinkedList(LinkedList):
    """Doubly Linked List"""
    def __init__(self) -> None:
        super().__init__()
    
    def insert(self, v):
        if not self.head:
            self.head = LNode(v)
            self.size = 1
            return
        p = self.head
        while p.next: p = p.next
        p.next = LNode(v)
        p.next.prev = p
        self.size += 1

    def delete(self, v):
        if self.head.value == v:
            self.head = self.head.next
            self.head.prev = None
            self.size -= 1
            return
        c = self.head.next
        while c and c.value != v:
            c = c.next
        if not c: return # not found
        c.prev.next = c.next
        if c.next: c.next.prev = c.prev
        self.size -= 1


if __name__ == '__main__':
  # testing
  dll = DoublyLinkedList()
  dll.insert(1)
  dll.insert(2)
  print(dll)
  len(dll)
  dll.delete(1)
  print(dll)
  dll.insert(1)
  print(dll)

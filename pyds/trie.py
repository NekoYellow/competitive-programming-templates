class _Node():
    def __init__(self, char=''):
        self.c = char
        self.s = {} # sons char->_Node
        self.cnt = 0 # number of '*'s below this node
    def __repr__(self):
        return str(self.s)

class Trie():
    def __init__(self, words=[]):
        self.root = _Node()
        for w in words:
            self.put(w)

    def put(self, word):
        """Put word `word` into trie."""
        p = self.root
        p.cnt += 1
        for c in word:
            if c not in p.s:
                p.s[c] = _Node(c)
            p = p.s[c]
            p.cnt += 1
        p.s['*'] = _Node('*') # end of word

    def contains(self, word):
        """Return if trie contains word `word`."""
        p = self.root
        for c in word:
            if c not in p.s:
                return False
            p = p.s[c]
        return '*' in p.s
    
    def search(self, word):
        """Search the shortest unique prefix of word `word` in trie."""
        if not self.contains(word):
            raise ValueError(f"Word {word} not found in trie!")
        prefix = ""
        p = self.root
        for c in word:
            p = p.s[c]
            prefix += c
            if p.cnt == 1:
                break
        return prefix
    
    def remove(self, word):
        """Remove word `word` from trie if exists."""
        if not self.contains(word):
            raise ValueError(f"Word {word} not found in trie!")
        def rm(p, w):
            p.cnt -= 1
            if not w:
                p.s.pop('*')
                return
            rm(p.s[w[0]], w[1:])
            if not p.s[w[0]].s:
                p.s.pop(w[0])
        rm(self.root, word)

    def traversal(self):
        """Return all words in trie."""
        words = []
        def dfs(p, w=""):
            if p.c == '*':
                words.append(w)
                return
            for nc in p.s:
                dfs(p.s[nc], w+p.c)
        dfs(self.root)
        return words
      
      
if __name__ == '__main__':
    def longestPrefix(words):
        trie = Trie(words)
        w = words[0]
        l = 0
        p = trie.root
        while len(p.s) == 1:
            if '*' in p.s: break
            p = p.s[w[l]]
            l += 1
        return w[:l]
    
    print(longestPrefix(["apple", "apple", "apple", "apple"]), \
          longestPrefix(["apple", "appetite", "apparatus", "appliance"]))
    
    def shortestUniPrefix(words):
        trie = Trie(words)
        res = []
        for w in words:
            res.append(trie.search(w))
        return res
    
    print(shortestUniPrefix(['apple', 'banana', 'cherry', 'cranberry', 'grape', 'grapefruit']))
    

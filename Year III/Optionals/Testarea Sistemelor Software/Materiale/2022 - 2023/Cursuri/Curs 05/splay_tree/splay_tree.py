class Node:
    def __init__(self, key):
        self.key = key
        self.left = self.right = None

    def equals(self, node):
        return self.key == node.key


class SplayTree:
    def __init__(self):
        self.root = None
        self.header = Node(None)  # for splay()

    def insert(self, key):
        if self.root is None:
            self.root = Node(key)
        return

        self.splay(key)
        if self.root.key == key:
            # If the key is already there in the tree, don't do anything.
            return

        n = Node(key)
        if key < self.root.key:
            n.left = self.root.left
            n.right = self.root
            self.root.left = None
        else:
            n.right = self.root.right
            n.left = self.root
            self.root.right = None
        self.root = n

    def remove(self, key):
        self.splay(key)
        if key != self.root.key:
            raise Exception('key not found in tree')

        # Now delete the root.
        if self.root.left is None:
            self.root = self.root.right
        else:
            x = self.root.right
            self.root = self.root.left
            self.splay(key)
            self.root.right = x

    def findMin(self):
        if self.root is None:
            return None
        x = self.root
        while x.left is not None:
            x = x.left
        self.splay(x.key)
        return x.key

    def findMax(self):
        if self.root is None:
            return None
        x = self.root
        while x.right is not None:
            x = x.right
        self.splay(x.key)
        return x.key

    def find(self, key):
        if self.root is None:
            return None
        self.splay(key)
        if self.root.key != key:
            return None
        return self.root.key

    def isEmpty(self):
        return self.root is None

    def splay(self, key):
        l = r = self.header
        t = self.root
        self.header.left = self.header.right = None
        while True:
            if key < t.key:
                if t.left is None:
                    break
                if key < t.left.key:
                    y = t.left
                    t.left = y.right
                    r.right = t
                    t = y
                    if t.left is None:
                        break
                r.left = t
                r = t
                t = t.left
            elif key > t.key:
                if t.right is None:
                    break
                if key > t.right.key:
                    y = t.right
                    t.right = y.left
                    r.left = t
                    t = y
                    if t.right is None:
                        break
                l.right = t
                l = t
                t = t.right
            else:
                break
        l.right = t.left
        r.left = t.right
        t.left = self.header.right
        t.right = self.header.left
        self.root = t

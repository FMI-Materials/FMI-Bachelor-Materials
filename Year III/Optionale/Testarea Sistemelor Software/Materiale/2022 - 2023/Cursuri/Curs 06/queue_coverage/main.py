# TASK:
#
# Achieve full statement coverage on the Queue class.

import array


class Queue:
    def __init__(self, size_max):
        assert size_max > 0
        self.max = size_max
        self.head = 0
        self.tail = 0
        self.size = 0
        self.data = array.array('i', range(size_max))

    def empty(self):
        return self.size == 0

    def full(self):
        return self.size == self.max

    def enqueue(self, x):
        if self.size == self.max:
            return False
        self.data[self.tail] = x
        self.size += 1
        self.tail += 1
        if self.tail == self.max:
            self.tail = 0
        return True

    def dequeue(self):
        if self.size == 0:
            return None
        x = self.data[self.head]
        self.size -= 1
        self.head += 1
        if self.head == self.max:
            self.head = 0
        return x

    def checkRep(self):
        assert self.tail >= 0
        assert self.tail < self.max
        assert self.head >= 0
        assert self.head < self.max
        if self.tail > self.head:
            assert (self.tail-self.head) == self.size
        if self.tail < self.head:
            assert (self.head-self.tail) == (self.max-self.size)
        if self.head == self.tail:
            assert (self.size==0) or (self.size == self.max)


def test():
    q = Queue(2)
    assert q
    q.checkRep()

    empty = q.empty()
    assert empty
    q.checkRep()

    full = q.full()
    assert not full
    q.checkRep()
    
    result = q.dequeue()
    assert result == None
    q.checkRep()
    
    result = q.enqueue(10)
    assert result == True
    q.checkRep()
    
    result = q.enqueue(20)
    assert result == True
    q.checkRep()
    
    empty = q.empty()
    assert not empty
    q.checkRep()
    
    full = q.full()
    assert full
    q.checkRep()
    
    result = q.enqueue(30)
    assert result == False
    q.checkRep()
    
    result = q.dequeue()
    assert result == 10
    q.checkRep()
    
    result = q.dequeue()
    assert result == 20
    q.checkRep()


test()


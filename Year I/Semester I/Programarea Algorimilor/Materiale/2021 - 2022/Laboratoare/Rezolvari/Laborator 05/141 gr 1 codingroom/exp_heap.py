#stiva  - adaugare, eliminare de la acelasi capat O(1)
#list - adaugare, eliminare la sfarsitul listei O(1)


#coada - adaugare la un capat, eliminare de la celalalt
#list - nu adaugare/eliminare de la inceput O(n)
#https://docs.python.org/3.9/library/collections.html?highlight=deque#collections.deque 
#https://docs.python.org/3/library/queue.html Queue - sincronizate -mai lente

import collections
q=collections.deque()
ls=[10,4,6,1,3,8]
for x in ls:
    q.append(x)
while len(q)>0:
    x=q.popleft()
    print(x,end=" ")
print()


#coada de prioritati - heap (ansamblu) - elementul extras este cel cu prioritatea cea mai mica/mare min-heap/max-heap O(log(n))

#https://docs.python.org/3/library/heapq.html 
#https://docs.python.org/3/library/queue.html#  PriorityQueue

import heapq
h=[] #vector-heap #python min-heap
ls=[10,4,6,1,3,8] 
for x in ls:
    heapq.heappush(h,x)
while len(h)>0:
    print(h)
    x=heapq.heappop(h) #scoate elementul cel mai mic in O(log(n))
    print(x,end=" ")
print()

import heapq
s = 0
h = []
for x in input().split():
    heapq.heappush(h, int(x))
while len(h) > 1:
    x = heapq.heappop(h)
    y = heapq.heappop(h)
    s = x + y + s
    heapq.heappush(h, x+y)
x = heapq.heappop(h)

print(s)

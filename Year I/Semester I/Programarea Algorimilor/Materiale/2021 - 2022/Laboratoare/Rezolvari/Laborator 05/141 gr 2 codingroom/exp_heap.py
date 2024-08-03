#structuri de date
#stiva - adaugari si eliminare de la acelasi capat
#implemnetare - list - adaugare/eliminare de la final O(1)

#coada - adaug la un capat si eliminare din celalalt capat
#list - nu complexitateta ad/elim la inceput O(n)
#https://docs.python.org/3.9/library/collections.html?highlight=deque#collections.deque  
#https://docs.python.org/3/library/queue.html - sincronizate -mai lente

import collections
ls=[4,1,7,2,9,8]
q=collections.deque()
for x in ls:
    q.append(x)
while len(q)>0:
    print(q.popleft(),end=" ")

print()

#coada prioritati - heap (ansamblu) - extragere - cel cu prioritatea cea mai mare/mica (min-heap, max-heap)
#min dintr-un vector -O(n)
#extragere/adaugare in heap - O(log(n))
#https://docs.python.org/3/library/heapq.html min-heap
#https://docs.python.org/3/library/queue.html - PriorityQueue
import heapq
ls=[4,1,7,2,9,8]
h=[]
for x in ls:
    heapq.heappush(h,x) #O(log(n))
while len(h)>0:
    x=heapq.heappop(h) #O(log(n))
    print(x,end=" ")

print()




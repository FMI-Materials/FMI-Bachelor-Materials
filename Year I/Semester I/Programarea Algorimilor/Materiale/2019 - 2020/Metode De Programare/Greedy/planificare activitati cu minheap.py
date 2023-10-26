from collections import deque
import heapq as hq
li=[('a',2, 100),('b',1,19), ('c',2,27), ('d',1,25),('e',3,15)]
Q=[]
plan=[]
hq.heapify(Q)
li.sort(key=lambda x:x[1],reverse=True)
lista=deque(li)
T=lista[0][1]
print(T)
while lista!=deque([]) and T>0:
    while lista!=deque([]) and lista[0][1]>=T:
         hq.heappush(Q,(lista[0][0],lista[0][1],lista[0][2]))
         lista.popleft()
    a=hq.heappop(Q)
    plan.append(a)
    T-=1
print(plan)
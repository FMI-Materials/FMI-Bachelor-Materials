n=13
l=[1,5,7]
from _collections import deque
q=deque([0])
v=[0]*(n+1)
while q:
    for coin in l:
        if q[0]+coin<=n  and v[q[0]+coin]==0:
            v[q[0]+coin]=coin
            q.append(q[0]+coin)
    q.popleft()
#v[i]-ultima bancnota folosita pentru a ajunge eficient la suma i
#v[i] e monede
print(v)
i=n
while i!=0:
    print(v[i])
    i-=v[i]

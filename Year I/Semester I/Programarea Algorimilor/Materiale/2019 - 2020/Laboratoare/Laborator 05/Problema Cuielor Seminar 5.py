a=[(1,2),(1,4),(2,3),(4,5)]
a.sort(key=lambda x: x[1])
from collections import deque
a=deque(a)
sol=[]
cui=-1
for x in a:
    if x[0]<=cui and cui<=x[1]:
        continue
    if x[0]>cui:
        sol.append(x[1])
        cui=x[1]
    if x[1]<cui:
        sol.pop()
        sol.append(x[1])
        cui=x[1]
print(len(sol))
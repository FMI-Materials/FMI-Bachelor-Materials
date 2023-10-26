# Lanturi minime intre doua noduri intr-un graf neorientat

f = open("graf.in")

lista = dict()

line = f.readline()
v = line.split()
n = int(v[0])
m = int(v[1])
for i in range(1,n+1):
    lista[i] = []
for i in range(m):
    line = f.readline()
    v = line.split()
    x = int(v[0])
    y = int(v[1])
    lista[x].append(y)
    lista[y].append(x)

print("Introduceti cele doua noduri:")
line = input()
v = line.split()
uu = int(v[0])
vv = int(v[1])

vizitat = [0] * (n+1)
tata = dict()
for i in range(1, n+1):
    tata[i] = []

d = [0] * (n+1)
parcurg = []

def BFS(start):
    from collections import deque
    q = deque([])
    q.append(start)
    vizitat[start] = 1
    d[start] = 0
    while len(q) > 0:
        x = q.popleft()
        parcurg.append(x)
        for j in lista[x]:
            if vizitat[j] == 0:
                q.append(j)
                vizitat[j] = 1
                tata[j].append(x)
                d[j] = d[x] + 1
            elif d[j] == d[x] + 1:
                tata[j].append(x)


BFS(uu)
c=[]


def listaNT(s):
        c.append(s)
        if s==uu:
            while len(c)>0 and len(tata[c[-1]])<=1:
                print(c.pop(), end=" ")
            if len(c)>0:
                c.reverse()
                print(*c)
                c.reverse()

        for t in tata[s]:
            listaNT(t)


listaNT(vv)
f.close()
f = open("input.in")

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


print("dati cele doua noduri: ")
u=int(input())
v=int(input())

viz=[0]*(n+1)
tata={}
for i in range (1,n+1):
    tata[i]=[]
d=[None]*(n+1)
parcurg=[]
def BF(s):
    from collections import deque
    q=deque([])
    q.append(s)
    viz[s]=1
    d[s]=0
    while len(q)>0:
        x=q.popleft()
        parcurg.append(x)
        for j in lista[x]:
            if viz[j]==0:
                q.append(j)
                viz[j]=1
                tata[j].append(x)
                d[j]=d[x]+1
            elif d[j]==d[x]+1:
                tata[j].append(x)


BF(u)
c=[]
comune=[0]*(n+1)
comune[u]=2
comune[v]=2
def listaNT(s):
        c.append(s)
        if s==u:
            while len(c)>0 and len(tata[c[-1]])<=1:
                varf=c.pop()
                if comune[varf]==0:
                    comune[varf]=1
            if len(c)>0:
                for varf in c:
                    if comune[varf] == 0:
                        comune[varf]=1

        for t in tata[s]:
            listaNT(t)

listaNT(v)
for i in range(1,n+1):
    if comune[i]==1:
        print(i, end=" ")


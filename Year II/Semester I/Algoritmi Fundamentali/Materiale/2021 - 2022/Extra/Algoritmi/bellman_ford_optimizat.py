# Algoritmul lui Bellman-Ford pentru determinarea distantelor de la un nod la celelalte noduri intr-un graf cu ponderi negative.
# O(n * m)
# !!!!!!!! Nu merge !!!!!!!!
from collections import deque

f = open("ponderi_negative.in")
line = f.readline()
v = line.split()
n = int(v[0])
m = int(v[1])


def citire(noduri, muchii, orientat):
    lista = dict()

    for i in range(1, noduri + 1):
        lista[i] = dict()

    for i in range(muchii):
        line = f.readline()
        v = line.split()
        x = int(v[0])
        y = int(v[1])
        cost = int(v[2])
        if orientat:
            lista[x][y] = cost
        else:
            lista[x][y] = cost
            lista[y][x] = cost

    return lista


lista = citire(n, m, 0)
start = 1
inf = float("infinity")
dist = [inf] * (n + 1)
vizitat = [0] * (n + 1)
tata = [0] * (n + 1)
nr = [0] * (n + 1)


def BellmanFord(start):
    q = deque([])
    q.append(start)
    vizitat[start] = 1
    while len(q) > 0:
        nod = q.popleft()
        vizitat[nod] = 0
        for vecin, cost in lista[nod].items():
            if dist[nod] < inf and dist[nod] + cost < dist[vecin]:
                dist[vecin] = dist[nod] + cost
                tata[vecin] = nod
                if vizitat[vecin] == 0:
                    q.append(vecin)
                    vizitat[vecin] = 1
                    nr[vecin] = nr[nod] + 1
                    if nr[vecin] > n - 1:
                        return vecin
    return None


x = BellmanFord(start)
print("Circuitul este: ")


def LANT(s):
    while s != tata[s]:
        print(s, end=" ")
        s = tata[s]
    else:
        print(s, end=" ")


if x != None:
    LANT(x)
else:
    print("Nu are circuit")
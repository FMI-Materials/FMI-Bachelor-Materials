import heapq
f = open("catun.in")
line = f.readline()
v = line.split()
N = int(v[0])
M = int(v[1])
K = int(v[2])

line = f.readline()
v = line.split()
fortareata = [int(x)  for x in v]
lista = dict()
for i in range(1, N + 1):
    lista[i] = []
for i in range(M):
    line = f.readline()
    v = line.split()
    x = int(v[0])
    y = int(v[1])
    z = int(v[2])
    lista[x].append((y,z))
    lista[y].append((x,z))

print(lista)
f.close()

def dijkstra(lista, fortareata):
    distante = {nod : float('infinity') for nod in lista.keys()}
    legatura = [0] * (N + 1)
    noduri = [0] * (N + 1)
    heap = []
    for x in fortareata:
        distante[x] = 0
        legatura[x] = x
        noduri[x] = x
        heapq.heappush(heap, (0, x))
    heapq.heapify(heap)
    while len(heap) > 0:
        dist, nod = heapq.heappop(heap)
        if dist <= distante[nod]:
            for (vecin, cost) in lista[nod]:
                if dist + cost < distante[vecin]:
                    distante[vecin] = dist + cost
                    legatura[vecin] = legatura[nod]
                    noduri [vecin] = vecin
                    heapq.heappush(heap, (dist + cost, vecin))
                elif dist + cost == distante[vecin] and legatura[nod] < legatura[vecin]:
                    distante[vecin] = dist + cost
                    legatura[vecin] = legatura[nod]
                    noduri[vecin] = vecin
                    heapq.heappush(heap, (dist + cost, vecin))
    return distante, legatura, noduri

distante, legaturi, noduri = dijkstra(lista, fortareata)
for i in range(1, N + 1):
    if i in fortareata:
        print(0, end = " ")
    else:
        print(legaturi[i], end=" ")
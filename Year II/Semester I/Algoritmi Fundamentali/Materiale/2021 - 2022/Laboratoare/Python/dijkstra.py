import heapq


f = open("dijkstra.in")

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
            lista[x][y] = cost;
        else:
            lista[x][y] = cost;
            lista[y][x] = cost;

    return lista


lista = citire(n, m, 0)
print(lista)



def dijkstra(lista, start):
    distante = {nod : float('infinity') for nod in lista.keys()}
    distante[start] = 0
    heap = [(0, start)]
    heapq.heapify(heap)
    while len(heap) > 0:
        dist, nod = heapq.heappop(heap)
        if dist <= distante[nod]:
            for vecin, cost in lista[nod].items():
                if dist + cost <= distante[vecin]:
                    distante[vecin] = dist + cost
                    heapq.heappush(heap, (dist + cost, vecin))

    return distante


start = 1
print(dijkstra(lista, start))










f.close()
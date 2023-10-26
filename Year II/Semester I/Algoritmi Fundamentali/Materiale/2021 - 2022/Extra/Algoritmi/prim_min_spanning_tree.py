# Algoritmul lui Prim pentru determinarea arborelui partial de cost minim.
import heapq

f = open("ponderi.in")
line = f.readline()
v = line.split()
n = int(v[0])
m = int(v[1])


def citire_matrice_liste(noduri,muchii,orientat):
    l = {}
    for i in range(1, noduri + 1):
        l[i] = []

    for i in range(muchii):
        line = f.readline()
        v = line.split()
        x, y, cost = v
        x = int(x)
        y = int(y)
        cost = int(cost)
        if orientat:
            l[x].append((y,cost))
        else:
            l[x].append((y,cost))
            l[y].append((x,cost))
    return l


lista = citire_matrice_liste(n, m, 0)
f.close()


def prim(start):
    global n, m, lista
    inf = float("Inf")
    h = []
    tata = [0] * (n + 1)
    vizitat = [0] * (n + 1)
    heapq.heapify(h)
    heapq.heappush(h, (0,start))
    dist = [inf] * (n + 1)
    dist[start] = 0

    while len(h) > 0:
        while len(h) and vizitat[h[0][1]]:
            heapq.heappop(h)
        if len(h) == 0:
            break
        t = heapq.heappop(h)
        nod = t[1]
        dd = t[0]
        vizitat[nod] = 1
        for vecin, cost in lista[nod]:
            if vizitat[vecin] == 0 and dist[vecin] > cost:
                dist[vecin] = cost
                tata[vecin] = nod
                heapq.heappush(h, (dist[vecin], vecin))

    return dist, tata

start = 9
dist, tata = prim(start)
cost_final = sum(dist[1:])

def gaseste_cost(nod, copil):
    for vecin, cost in lista[nod]:
        if vecin == copil:
            return cost
    return -1


def print_muchii(tata):
    cost_total = 0
    for x in range(1, n + 1):
        if tata[x] != 0:
            cost = gaseste_cost(x, tata[x])
            cost_total += cost
            print(x, tata[x], cost)
    print(f"Costul total este: {cost_final}\n")


print_muchii(tata)
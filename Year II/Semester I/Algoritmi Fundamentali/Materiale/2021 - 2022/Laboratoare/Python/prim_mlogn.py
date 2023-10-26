import heapq

f = open("prim.in")
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


lista = citire_matrice_liste(n,m,0)
def prim(start):
    inf = 1<<25
    global n,m, lista
    h = []
    tata = [0] * (n+1)
    vizitat = [0] * (n+1)
    heapq.heapify(h)
    heapq.heappush(h,(0, start))
    dist = [inf] * (n+1)
    dist[start] = 0
    while len(h)>0:
        while len(h) and vizitat[h[0][1]]:
            heapq.heappop(h)
        if len(h) == 0:
            break
        t = heapq.heappop(h)
        x = t[1]
        vizitat[x] = 1
        for vecin in lista[x]:
            if vizitat[vecin[0]] == 0 and dist[vecin[0]] > vecin[1]:
                dist[vecin[0]] = vecin[1]
                tata[vecin[0]] = x
                heapq.heappush(h, (dist[vecin[0]], vecin[0]))

    return dist, tata


print("Introduceti nodul de start:")
start = int(input())
dist, tata = prim(start)
final_dist = sum(dist[1:])

def print_muchii(tata):
    for x in range(1,n+1):
        if tata[x] != 0:
            print(x , tata[x])

print_muchii(tata)
print(f"dist : {dist[1:]}")
print(final_dist)
print(f"tata : {tata[1:]}")




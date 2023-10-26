# Determinarea muchiilor critice dintr-un graf.

f = open("graf.in")
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
        x, y = v
        x = int(x)
        y = int(y)
        if orientat:
            l[x].append(y)
        else:
            l[x].append(y)
            l[y].append(x)
    return l


lista = citire_matrice_liste(n, m, 0)
f.close()
muchii_critice = []
vizitat = [0] * (n + 1)
discovery_time = [float("Inf")] * (n + 1)
low = [float("Inf")] * (n + 1)
parent = [-1] * (n + 1)
time = 0


def DFS(nod):
    global lista, vizitat, discovery_time, low, muchii_critice, parent, time

    vizitat[nod] = 1
    discovery_time[nod] = time
    low[nod] = time
    time += 1

    for vecin in lista[nod]:
        if vizitat[vecin] == 0:
            parent[vecin] = nod
            DFS(vecin)
            low[nod] = min(low[nod], low[vecin])
            if low[vecin] > discovery_time[nod]:
                muchii_critice.append((nod, vecin))
        elif vecin != parent[nod]:
            low[nod] = min(low[nod], discovery_time[vecin])




for i in range(1, n + 1):
    if vizitat[i] == 0:
        DFS(i)
if len(muchii_critice) == 0:
    print("Nu exista muchii critice.")
else:
    print("Muchii critice:", *muchii_critice)
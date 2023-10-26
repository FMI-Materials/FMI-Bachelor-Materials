# BFS
import queue

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
        if orientat:
            l[int(v[0])].append(int(v[1]))
        else:
            l[int(v[0])].append(int(v[1]))
            l[int(v[1])].append(int(v[0]))
    return l


lista = citire_matrice_liste(n, m, 0)
f.close()

vizitat = [0] * (n + 1)
tata = [0] * (n + 1)
dist = [None] * (n + 1)
parcurg = []


def BFS(start):
    global lista, tata, vizitat, parcurg, dist
    coada = []
    coada.append(start)
    vizitat[start] = 1
    dist[start] = 0

    while len(coada) > 0:
        nod = coada.pop(0)
        parcurg.append(nod)
        for vecin in lista[nod]:
            if vizitat[vecin] == 0:
                coada.append(vecin)
                vizitat[vecin] = 1
                tata[vecin] = nod
                dist[vecin] = dist[nod] + 1


def afisare(start):
    while start != 0:
        print(start, end = " ")
        start = tata[start]


start = 1
BFS(start)
print(parcurg)
# DFS.
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


lista = citire_matrice_liste(n,m,0)
vizitat = [0] * (n + 1)
tata = [ -1 ] * (n + 1)
parcurge = []


def DFS(nod):
    global vizitat, tata, lista, parcurge
    vizitat[nod] = 1
    for vecin in lista[nod]:
        if vizitat[vecin] == 0:
            parcurge.append(vecin)
            tata[vecin] = nod
            DFS(vecin)


start = 1
DFS(start)
parcurge.insert(0, start)
print(parcurge)

# def afisare(start):
#     parcurg = []
#     while start > 0:
#         parcurg.append(start)
#         start = tata[start]
#     return parcurg
#
#
# parcurg = afisare(start)
# parcurg = parcurg.reverse()
# print(parcurg)
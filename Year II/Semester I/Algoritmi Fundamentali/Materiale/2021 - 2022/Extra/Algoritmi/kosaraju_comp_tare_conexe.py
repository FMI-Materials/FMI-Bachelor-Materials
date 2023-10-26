# Algoritmul lui Kosaraju pentru determinarea componentelor tare conexe.

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


lista = citire_matrice_liste(n, m, 1)
f.close()
vizitate = [0] * (n + 1)
stiva = []


def DFS(nod):
    vizitate[nod] = 1
    for vecin in lista[nod]:
        if vizitate[vecin] == 0:
            DFS(vecin)
    stiva.append(nod)


def DFS_transpusa(nod, numar, transpusa, selectate):
    selectate[nod] = numar
    for vecin in transpusa[nod]:
        if selectate[vecin] == 0:
            DFS_transpusa(vecin, numar, transpusa, selectate)


for i in range(1, n + 1):
    if vizitate[i] == 0:
        DFS(i)

sortate = []
for i in range(len(stiva) - 1, -1, -1):
    sortate.append(stiva[i])


def matrice_transpusa(lista):
    transpusa = {}
    for i in range(1, n + 1):
        transpusa[i] = []

    for nod in range(1, n + 1):
        for vecin in lista[nod]:
            transpusa[vecin].append(nod)

    return transpusa


def componente_conexe():
    global lista, sortate

    transpusa = matrice_transpusa(lista)
    selectate = [0] * (n + 1)
    nr = 0
    for nod in sortate:
        if selectate[nod] == 0:
            nr = nr + 1
            DFS_transpusa(nod, nr, transpusa, selectate)

    return selectate, nr


componente, nr = componente_conexe()
for com in range(1, nr + 1):
    for nod in range(1, n + 1):
        if componente[nod] == com:
            print(nod, end = " ")
    print()


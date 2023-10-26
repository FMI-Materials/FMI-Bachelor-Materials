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
nivel = [0] * (n + 1)
nivel_minim = [0] * (n + 1)

ok = 0


def DFS(nod):
    global vizitat, lista, nivel, nivel_minim, ok
    vizitat[nod] = 1
    nivel_minim[nod] = nivel[nod]

    for y in lista[nod]:
        if vizitat[y] == 0:
            nivel[y] = nivel[nod] + 1
            DFS(y)
            nivel_minim[nod] = min(nivel_minim[nod], nivel_minim[y])
            if nivel_minim[y] > nivel[nod]:
                print("muchia critica: ", nod, y, sep = " ")
                ok = 1
        elif nivel[y] < nivel[nod] - 1:
            nivel_minim[nod] = min(nivel_minim[nod], nivel[y])


start = 1
DFS(start)
if ok == 0:
    print("retea 2 muchie-conexa")
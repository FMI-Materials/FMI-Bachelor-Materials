
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


lista = citire_matrice_liste(n,m,1)
vizitat = [0] * (n + 1)
tata = [0] * (n + 1)
final = [0] * (n + 1)
ok = 0

def DFS(nod):
    global vizitat, tata, lista, ok
    vizitat[nod] = 1
    for y in lista[nod]:
        if ok != 0:
            break
        if vizitat[y] == 0:
            tata[y] = nod
            DFS(y)
        elif final[y] != 1:
            print("ciclu elementar")
            v = nod
            while v != y:
                print(v, end = " ")
                v = tata[v]
            print(y, sep = " ")
            ok = 1
    final[nod] = 1


def afis(start):
    while start != 0:
        print(start, end = " ")
        start = tata[start]

start = 1
DFS(start)
if ok == 0:
    print("Realizabil")
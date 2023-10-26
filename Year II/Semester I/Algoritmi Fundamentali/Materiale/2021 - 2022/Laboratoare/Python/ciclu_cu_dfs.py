
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
tata = [0] * (n + 1)
parcurg = []
ok = 0

def DFS(nod):
    global vizitat, tata, lista, ok
    vizitat[nod] = 1
    if ok == 0:
        for y in lista[nod]:
            if vizitat[y] == 0:
                tata[y] = nod
                parcurg.append(y)
                DFS(y)
                if ok == 1:
                    return
            elif y != tata[nod]:
                print("ciclu elementar")
                v = nod
                nr = 1
                while v != y:
                    print(v, end = " ")
                    nr = nr + 1
                    v = tata[v]
                print(y, nod, sep = " ")
                ok = 1
start = 1
DFS(start)
print(parcurg)
if ok == 0:
    print("graf aciclic")
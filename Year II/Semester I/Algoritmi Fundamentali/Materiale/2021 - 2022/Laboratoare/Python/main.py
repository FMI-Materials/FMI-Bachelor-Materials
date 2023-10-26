f = open("graf.in")
line = f.readline()
v = line.split()

nrNoduri = int(v[0])
nrMuchii = int(v[1])


def citire_matrice_adiacenta(noduri, muchii, orientat):
    matrice=[]
    for i in range (noduri + 5):
        m=[]
        for j in range(noduri + 5):
            m.append(0)
        matrice.append(m)
    for i in range(muchii):
        line=f.readline()
        v=line.split()
        print(v)
        if orientat:
            matrice[int(v[0])][int(v[1])] = 1
        else:
            matrice[int(v[0])][int(v[1])] = 1
            matrice[int(v[1])][int(v[0])] = 1
    return matrice


graf_neorientat_adiacenta = citire_matrice_adiacenta(nrNoduri, nrMuchii, 0)

print(graf_neorientat_adiacenta)
f.close()

f = open("graf.in")
line = f.readline()
v = line.split()

nrNoduri = int(v[0])
nrMuchii = int(v[1])

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

lista = citire_matrice_liste(nrNoduri,nrMuchii,0)
print(lista)
f.close()

def trecere_adiacenta_liste(matrice, noduri):
    lista = {}
    for i in range(1, noduri + 1):
        lista[i] = []
    for i in range(noduri):
        for j in range(noduri):
            if matrice[i][j] == 1:
                lista[i].append(j)
    return lista

l = trecere_adiacenta_liste(graf_neorientat_adiacenta, nrNoduri)
print(l)

def trecere_liste_adiacenta(lista, noduri):
    matrice = []
    for i in range(noduri + 1):
        m = []
        for j in range(noduri + 1):
            m.append(0)
        matrice.append(m)
    for i in range(1, noduri + 1):
        v = lista[i]
        for x in v:
            matrice[i][x] = 1
            matrice[x][i] = 1
    return matrice

mat = trecere_liste_adiacenta(l, nrNoduri)
print(mat)
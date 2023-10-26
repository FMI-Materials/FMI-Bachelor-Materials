
# Se citesc informații despre un graf neorientat ponderat conex G din fișierul graf.in.
# Fișierul are următoarea structură:
# - pe prima linie sunt două numere reprezentând numărul de vârfuri n (n>4) și numărul de
# muchii m ale grafului, m>n
# - pe următoarele m linii sunt câte 3 numere pozitive reprezentând extremitatea inițială,
# extremitatea finală și costul unei muchii din graf
# a) Să se afișeze costul unui arbore parțial de cost minim în G. Complexitate O(mlog(n)).
# b) Se citesc de la tastatură două muchii noi date tot prin extremitatea inițială, extremitatea
# finală și cost. Știind că doar una dintre aceste muchii se va adăuga la graful G, decideți pe
# care o adăugați astfel încât noul graf să aibă un arbore parțial de cost minim cu cost cât mai
# mic și afișați muchiile unui arbore parțial de cost minim în acest graf. Complexitate O(n)

f = open("graf.in")
line = f.readline()
v = line.split()
n = int(v[0])
m = int(v[1])

lista = []
for i in range(m):
    line = f.readline()
    v = line.split()
    x, y, cost = v
    x = int(x)
    y = int(y)
    cost = int(cost)
    t = (x, y, cost)
    lista.append(t)
f.close()
parent = [0] * (n + 1)
rank = [0] * (n + 1)

def gaseste(nod):
    if parent[nod] == 0:
        return nod
    parent[nod] = gaseste(parent[nod])
    return parent[nod]


def intersectie(nod1, nod2, parent, rank):
    radacina_nod1 = gaseste(nod1)
    radacina_nod2 = gaseste(nod2)

    if rank[radacina_nod1] < rank[radacina_nod2]:
        parent[radacina_nod1] = radacina_nod2
    elif rank[radacina_nod1] > rank[radacina_nod2]:
        parent[radacina_nod2] = radacina_nod1
    else:
        parent[radacina_nod2] = radacina_nod1
        rank[radacina_nod1] += 1


def kruskal(lista):
    selectate = []
    sortate = sorted(lista, key = (lambda e: e[2]))
    nr_muchii = 0
    cost = 0
    for muchie in sortate:
        x = muchie[0]
        y = muchie[1]
        parent_x = gaseste(x)
        parent_y = gaseste(y)
        if parent_x != parent_y:
            selectate.append((x, y, muchie[2]))
            intersectie(x, y, parent, rank)
            cost += muchie[2]
            nr_muchii += 1
            if nr_muchii == n - 1:
                break

    return selectate, cost



selected, cost = kruskal(lista)
print(selected)
print("a)")
print(cost)
print("b)")

mList = [[] for x in range(n + 1)]
for (x, y, cos) in selected:
    mList[x].append((y, cos))
    mList[y].append((x, cos))

print("Intrare de la tastatura")
line = input()
v = line.split()
muchie1 = (int(v[0]), int(v[1]), int(v[2]))

line = input()
v = line.split()
muchie2 = (int(v[0]), int(v[1]), int(v[2]))

# print(muchie1)
# print(muchie2)


def DFS(nod1, nod2, vizitat, parcurge, ret, cost_curent, costuri):
    global mList
    if nod1 == nod2:
        ret.extend(parcurge)
        costuri.extend(cost_curent)
        return

    vizitat[nod1] = 1
    for (vecin, cost) in mList[nod1]:
        if vizitat[vecin] == 0:
            parcurge.append(vecin)
            cost_curent.append(cost)
            DFS(vecin, nod2, vizitat, parcurge, ret, cost_curent, costuri)
            parcurge.pop()
            cost_curent.pop()


vizitat1 = [0] * (n + 2)
parcurge1 = []
costuri1 = []
vizitat2 = [0] * (n + 2)
parcurge2 = []
costuri2 = []

DFS(muchie1[0], muchie1[1], vizitat1, [], parcurge1, [], costuri1)
DFS(muchie2[0], muchie2[1], vizitat2, [], parcurge2, [], costuri2)

max1 = max(costuri1)
edge1 = (0, 0, 0)
for edge in lista:
    if edge[2] == max1:
        edge1 = edge
max2 = max(costuri2)
edge2 = (0, 0, 0)
for edge in lista:
    if edge[2] == max2:
        edge2 = edge

cost_m1 = cost_m2 = cost

if muchie1[2] < max1:
    cost_m1 = cost_m1 - max1 + muchie1[2]
if muchie2[2] < max2:
    cost_m2 = cost_m2 - max2 + muchie2[2]

if cost_m1 < cost_m2:
    print(f"Adaugam: {muchie1[0]} {muchie1[1]}")
    print("Alegem sa adaugam prima muchie, cost nou: ", cost_m1)
    for edge in selected:
        if edge == edge1:
            print(muchie1)
        else:
            print(edge)
else:
    print(f"Adaugam: {muchie2[0]} {muchie2[1]}")
    print("Alegem sa adaugam a 2 a muchie, cost nou: ", cost_m2)
    for edge in selected:
        if edge == edge2:
            print(muchie1)
        else:
            print(edge)


# Algoritmul lui Kruskal pentru determinarea Minimum Spanning Tree.

f = open("ponderi.in")
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
print(cost)
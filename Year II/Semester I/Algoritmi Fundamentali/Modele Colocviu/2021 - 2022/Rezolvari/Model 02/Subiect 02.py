# functie ce returneaza o lista
# de muchii si ponderile lor

def listaMuchii(fisier):
    
    f = open(fisier)

    m = int(f.readline().split()[1])
    lista = [[] for _ in range(m)]

    i = 0
    for linie in f:
        lista[i] = [int(x) for x in linie.split()]
        i = i + 1

    lista.sort(key = lambda x : x[2])

    f.close()

    return lista

# functie ce uneste doua componente din graf
# prin cele doua noduri trimise ca parametru

def union(nod1, nod2, marker):

    m1 = marker[nod1 - 1]
    m2 = marker[nod2 - 1]

    for i in range (len(marker)):
        if marker[i] == m2:
            marker[i] = m1

def kruskal(lista):

    global n, marker
    arbore = []
    numar = 0
    marker = [i for i in range(n)]

    costMinim = 0

    for muchie in lista:

        # daca cele doua varfuri nu sunt deja unite
        # le adaugam in arborele de cost minim

        if marker[muchie[0] - 1] != marker[muchie[1] - 1]:
            
            arbore.append(muchie)

            # marcam cele doua noduri cu acelasi numar
            # pentru a arata ca sunt unite
            union(muchie[0], muchie[1], marker)
            costMinim = costMinim + muchie[2]

            numar = numar + 1
        
            if (numar == n - 1):
                break
    
    return arbore, costMinim

# lista muchii sortate crescator in functie de cost
# cuprinde elemente de genul: [nod1, nod2, cost]
lista = listaMuchii("graf.in")

f = open("graf.in", "r")

n, m = [int(x) for x in f.readline().split()]

# lista prin care tin cont care
# noduri sunt unite intre ele
marker = [i for i in range(n)]

# a)
arboreCostMinim, costMinim = kruskal(lista)

print(costMinim)

# b)

# citim cele 2 muchii de la tastatura
muchie1 = [int(x) for x in input().split()]
muchie2 = [int(x) for x in input().split()]

m = m + 1

# aplicam algoritmul lui kruskal adaugand
# pe rand cele 2 muchii in graf si comparam
# costurile finale pentru a vedea care este
# cel de cost minim

lista.append(muchie1)
lista.sort(key = lambda x : x[2])
arbore1, cost1 = kruskal(lista)

lista.remove(muchie1)
lista.append(muchie2)
lista.sort(key = lambda x : x[2])
arbore2, cost2 = kruskal(lista)

# afisam muchia adaugata si arborele
# de cost minim dupa adaugarea acesteia

if cost1 < cost2:
    print(f"adaugam {muchie1[0]} {muchie1[1]}")
    for i in range(n - 1):
        print(arbore1[i][0], arbore1[i][1])
else:
    print(f"adaugam {muchie2[0]} {muchie2[1]}")
    for i in range(n - 1):
        print(arbore2[i][0], arbore2[i][1])

f.close()
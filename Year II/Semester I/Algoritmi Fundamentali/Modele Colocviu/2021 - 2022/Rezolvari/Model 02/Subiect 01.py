# functie care prelucreaza fisierul de intrare
# se creeaza o lista de liste de tupluri
# unde fiecare tuplu contine un nod si distanta
# de la nodul i la nodul din tuplu

def listaAdiacenta(fisier):
    
    global n
    
    f = open(fisier)

    n = int(f.readline())
    lista = [ [] for _ in range(n) ]

    for i in range(n):
        linie = [int(x) for x in f.readline().split()]

        index = 1
        for j in range(linie[0]):
            lista[i].append((linie[index], linie[index + 1]))
            index = index + 2

    for i in range(n):
        lista[i].sort()

    s = int(f.readline())

    f.close()

    return lista, s

# parcurgem graful cu bfs si la fiecare pas
# verificam care este distanta minima intre varfuri

def drumBfs(lista, start):
    vizitat.append(start)
    coada.append(start)
    distanta[start - 1] = 0
    tata[start - 1] = 0

    while coada:
        s = coada.pop(0)

        for vecin in lista[s - 1]:
            if vecin[0] not in vizitat:
                vizitat.append(vecin[0])
                coada.append(vecin[0])
                if s != start:
                    distanta[vecin[0] - 1] = min(distanta[s - 1], vecin[1])
                    tata[vecin[0] - 1] = s
                # deoarece distanta de la nodul de start la el insusi
                # este 0 si nu dorim sa fie aceasta luata ca minim
                else:
                    distanta[vecin[0] - 1] = vecin[1]
                    tata[vecin[0] - 1] = start

    return distanta

# functia va returna o lista cu urmatoarea
# structura: [[(nod1, pondere1), (nod2, pondere2)],..]
# fiecare nod avand o lista corespunzatoare
# si nodul de start s
lista, s = listaAdiacenta("graf.in")

coada = []
vizitat = []

# lista in care se va calcula distanta de la
# nodul de start la fiecare nod din graf
distanta = [-1 for _ in range(n)]
tata = [0] * n

drumBfs(lista, s)

# a)
for i in range(len(distanta)):
    print(f"{i + 1}: {distanta[i]} ")
print()

# b)

capacitateMinima = 9999999

for i in range(len(distanta)):
    if i + 1 != s and distanta[i] < capacitateMinima:
        capacitateMinima = distanta[i]
        index = i + 1

lant = []

# mergem in vectorul de tati pentru a reconstrui
# drumul traseului de capacitate minima
while index != 0:
    lant.append(index)
    index = tata[index - 1]

lant.reverse()

print(f"Capacitatea minima este {capacitateMinima} pentru lantul", end = " ")
for nod in lant:
    print (nod, end = " ")
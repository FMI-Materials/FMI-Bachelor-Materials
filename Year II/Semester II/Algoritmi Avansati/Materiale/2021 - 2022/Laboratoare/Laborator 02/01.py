import math

def citire(fisier):
    f = open(fisier)
    orase = []

    for linie in f:
        orase.append([x.rstrip("\n") for x in linie.split(", ")])

    return orase

def distantaEuclidiana(oras1, oras2):
    return math.sqrt((int(oras2[1]) - int(oras1[1]))**2 + (int(oras2[2]) - int(oras1[2]))**2)

def graf(orase):
    graf = []

    for i in range(len(orase) - 1):
        for j in range(i + 1,len(orase)):
            l = [orase[i][0], orase[j][0], distantaEuclidiana(orase[i], orase[j])]
            graf.append(l)

    return graf

# implementare brute force a
# problemei comis voiajorului
# complexitate de timp: O(n!)

def backtracking(orase, numeOrase, cost, current):
    global aux
    numeOrase.remove(current)
    solution.append(current)
    for oras in numeOrase:
        solution.append(oras)
        c = [x for x in orase if x[0] == current][0]
        o = [x for x in orase if x[0] == oras][0]
        distances.append(cost + distantaEuclidiana(c, o))

        backtracking(orase, numeOrase, cost, numeOrase[0])

orase = citire("input.in")
d = distantaEuclidiana(orase[0], orase[1])

numeOrase = []
for oras in orase:
    oras = oras[0]
    numeOrase.append(oras)

current = numeOrase[0]
solution = []
distances = []

backtracking(orase, numeOrase, 0, current)
print(sum(distances))

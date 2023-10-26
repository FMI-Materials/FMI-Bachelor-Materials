import heapq
f = open("clustering.in")


def Levenshtein(word1, word2):
    if len(word2) == 0:
        return len(word1)
    elif len(word1) == 0:
        return len(word2)
    elif word1[0] == word2[0]:
        return Levenshtein(word1[1:], word2[1:])
    else:
        return 1 + min(Levenshtein(word1, word2[1:]), Levenshtein(word1[1:], word2), Levenshtein(word1[1:], word2[1:]))


line = f.readline()
v = line.split()
cuvinte = [x for x in v]
print(cuvinte)
f.close()

lista = []
for i in range(len(cuvinte)):
    for j in range(i + 1, len(cuvinte)):
        dist = Levenshtein(cuvinte[i], cuvinte[j])
        lista.append((i, j, dist))

print(lista)

def radacina(u):
    #determinare radacina arbore care contine u
    global tata
    if tata[u] ==0:
        return u
    tata[u] = radacina(tata[u])
    return tata[u]


def reuniune_ponderata(u,v):
    #reuniune ponderata
    global tata,h
    ru = radacina(u)
    rv = radacina(v)

    if h[ru] > h[rv]:
        tata[rv] = ru
    else:
        tata[ru] = rv
        if h[ru] == h[rv]:
            h[rv] = h[rv]+1

n = 0
n = len(cuvinte)
tata = [0] * (n)
h = [0] * (n)
lista_sortata = sorted(lista, key = lambda e : e[2])

nr_muchii_selectate = 0
cost = 0
arbore = []
i = 0
k = int(input())
while i < len(lista_sortata):
    m = lista_sortata[i]
    if radacina(m[0]) != radacina(m[1]):
        arbore.append((m[0], m[1]))
        reuniune_ponderata(m[0], m[1])
        cost = cost + m[2]
        nr_muchii_selectate = nr_muchii_selectate + 1
        if nr_muchii_selectate == n - k:
            break
    i = i + 1

print(tata)
for i in range(n):
    if tata[i] == 0:
        #print(cuvinte[i], end = " ")
        for j in range(n) :
            if radacina(j) == i:
                print(cuvinte[j], end = " ")
        print()









# from collections import deque
#
# f = open("drum_critic.in")
#
# line = f.readline()
# n = int(line)
#
# line = f.readline()
# durata = dict()
# v = line.split()
# durata = [ int(x) for x in v ]
# line = f.readline()
# m = int(f.readline())
#
# def aux(nod, viz, sortate):
#     global n, lista
#
#     viz[nod] = True
#     if nod in lista.keys():
#         for vecin, cost in lista[nod]:
#             if viz[vecin] == False:
#                 aux(vecin,viz, sortate)
#
#     sortate.insert(0, nod);
#
#
# def sortare_topologica():
#     global n, lista
#     viz = [False] * (n + 1)
#     sortate = []
#
#     for i in range(1, n + 1):
#         if viz[i] == False:
#             aux(i, viz, sortate)
#     return sortate
#
#
# def citire_muchii(noduri, muchii, orientat):
#     global durata
#     lista = dict()
#     for x in range( noduri + 1):
#         lista[x] = []
#
#     for i in range(muchii):
#         line = f.readline()
#         v = line.split()
#         x = int(v[0])
#         y = int(v[1])
#         if orientat:
#             lista[x].append((y,durata[x - 1]))
#         else:
#             lista[x].append((y, durata[x - 1]))
#             lista[y].append((x, durata[y - 1]))
#
#     return lista
#
#
# lista = citire_muchii(n, m, 1)
#
#
# sortat = sortare_topologica()
# start = 0
# dist = [ -float("infinity")] * (n + 2)
# dist[start] = 0
# tata = [0] * (n + 2)
#
#
# f.close()

from queue import Queue

file = open('graf.in', 'r')


def citire():
    line = file.readline()
    n = int(line)
    cost_muchie = [int(x) for x in next(file).split()]

    lista = [[] for i in range(n + 2)]
    d_intern = [0 for i in range(n + 2)]
    d_extern = [0 for i in range(n + 2)]

    line = file.readline()
    muchii = int(line)

    for i in range(muchii):
        line = file.readline().split()
        nod1 = int(line[0])
        nod2 = int(line[1])
        cost_var = cost_muchie[nod1 - 1]
        lista[nod1].append((nod2, cost_var))
        d_intern[nod2] = d_intern[nod2] + 1
        d_extern[nod1] = d_extern[nod1] + 1

    # adaugare nod s=0
    for i in range(1, n + 1):
        if d_intern[i] == 0:
            lista[0].append((i, 0))
    # adaugare nod s=n+1
    nod_T = n + 1
    for i in range(1, n + 1):
        if d_extern[i] == 0:
            lista[i].append((nod_T, cost_muchie[i - 1]))

    return lista, n, muchii, d_intern, d_extern, cost_muchie, nod_T


def sortare_topologica():
    queue = Queue(maxsize=n + 2)

    # adaugam in coada toate nodurile care au grad_intern 0
    for i in range(0, n + 2):
        if d_intern[i] == 0:
            queue.put(i)
    #

    while queue.empty() == False:
        i = queue.get()
        sortare.append(i)
        for vecin in lista[i]:
            d_intern[vecin[0]] = d_intern[vecin[0]] - 1
            if d_intern[vecin[0]] == 0:
                queue.put(vecin[0])


def det_drum_maxim(s):
    # d[toate vf cu grad intern 0]
    d[s] = 0
    for u in sortare:
        for vecin in lista[u]:
            v = vecin[0]
            cost = vecin[1]
            if d[u] + cost > d[v]:
                d[v] = d[u] + cost
                tata[v] = u


lista, n, muchii, d_intern, d_extern, cost_muchie, nod_T = citire()  # graful este doar orientat la sortare topologica
# print(lista)
# print(cost_muchie)
# vizitat=[0 for i in range(n+1)]
tata = [0 for i in range(n + 2)]
d = [-9999999 for i in range(n + 2)]
sortare = []

# vom apela sortarea topologica

sortare_topologica()
# print(sortare)

# avem s=0 varful de start(S)
# avem s=7 varful de final (T)
# am determinat sortarea topologica
det_drum_maxim(0)
# print(d)
# print(tata)
nod = nod_T  # nodul de final(T)

# reconstituire drum maxim
drum_recon = []
while nod != 0:  # nodul de inceput(S)
    if nod != nod_T and nod != 0:
        drum_recon.append(nod)  # activitate critica
    nod = tata[nod]

drum_recon.reverse()
print(drum_recon)

# [0, 1, 2, 3,  4,  5,  6,  nod_T]
# [0, 0, 7, 12, 0,  42,  42,  47]

file.close()

out = open('graf.out', 'w')
out.close()
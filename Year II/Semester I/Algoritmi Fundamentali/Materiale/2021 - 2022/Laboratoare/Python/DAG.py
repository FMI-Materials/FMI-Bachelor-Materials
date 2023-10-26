# from collections import deque
#
# f = open("DAG.in")
# n = int(f.readline())
# line = f.readline()
# v = line.split()
# durata = [int(x) for x in v]
# m = int(f.readline())
#
# grad_intern = [0] * (n + 1)
# graf_extern = [0] * (n + 1)
# precedenta = dict()
# for i in range(n):
#     precedenta[i] = []
#
# for i in range(m):
#     line = f.readline()
#     v = line.split()
#     x = int(v[0])
#     y = int(v[1])
#     grad_intern[y] += 1
#     graf_extern[x] += 1
#     cost = durata[x-1]
#     precedenta[x].append((y, cost))
# f.close()
#
# for i in range(1, n + 1):
#     if grad_intern[i] == 0:
#         precedenta[0].append((i,0))
# nod = n + 1
# for i in range(1, n + 1):
#     if graf_extern[i] == 0:
#         precedenta[i].append((nod, durata[i - 1]))
#
# sortare = []
# def sortare_topologica():
#     q = deque()
#     for i in range(0, n + 1):
#         if grad_intern[i] == 0:
#             q.append(i)
#
#     while len(q) != 0:
#         nod = q.pop()
#         sortare.append(nod)
#         for vecin in precedenta[nod]:
#             grad_intern[vecin[0]] -= 1
#             if grad_intern[vecin[0]] == 0:
#                 q.append(vecin[0])
#
# dist = [0] * (n + 2)
# tata = [0] * (n + 2)
# def det_drum_maxim(start):
#     dist[start] = 0
#     for u in sortare:
#         for vecin in precedenta[u]:
#             v = vecin[0]
#             cost = vecin[1]
#             if dist[u] + cost > dist [v]:
#                 dist[v] = dist[u] + cost
#                 tata[v] = u


from queue import Queue

file = open('DAG.in', 'r')


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

print("\n")
for i in range(1,n+1):
    print(f"{i}: {d[i]} {d[i]+cost_muchie[i-1]}")

# [0, 1, 2, 3,  4,  5,  6,  nod_T]
# [0, 0, 7, 12, 0,  42,  42,  47]

file.close()

out = open('graf.out', 'w')
out.close()
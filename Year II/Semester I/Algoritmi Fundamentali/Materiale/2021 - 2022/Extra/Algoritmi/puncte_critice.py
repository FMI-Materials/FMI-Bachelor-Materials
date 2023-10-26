# Determinarea punctelor critice dintr-un graf

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


# lista = citire_matrice_liste(n, m, 0)
# f.close()
# puncte_critice = []
# vizitat = [0] * (n + 1)
# nivel = [0] * (n + 1)
# nivel_minim = [0] * (n + 1)
# start = 1
#
#
# def DFS(nod):
#     global lista, vizitat, nivel, nivel_minim, puncte_critice, start
#     vizitat[nod] = 1
#     nivel_minim[nod] = nivel[nod]
#     for vecin in lista[nod]:
#         if vizitat[vecin] == 0:
#             nivel[vecin] = nivel[nod] + 1
#             DFS(vecin)
#             nivel_minim[nod] = min(nivel_minim[nod], nivel_minim[vecin])
#             if nivel_minim[vecin] >= nivel[nod] and (nod not in puncte_critice) and nod != start:
#                 puncte_critice.append(nod)
#         elif nivel[vecin] < nivel[nod] + 1:
#             nivel_minim[nod] = min(nivel_minim[nod], nivel[vecin])
#
#
# DFS(start)
# if len(puncte_critice) > 0:
#     print("Punctele critice: ", *puncte_critice)
# else:
#     print("Nu avem puncte critice")

lista = citire_matrice_liste(n, m, 0)
f.close()
puncte_critice = [False] * (n + 1)
vizitat = [0] * (n + 1)
discovery_time = [float("Inf")] * (n + 1)
low = [float("Inf")] * (n + 1)
parent = [-1] * (n + 1)
time = 0


def DFS(nod):
    global lista, vizitat, discovery_time, low, muchii_critice, parent, time

    vizitat[nod] = 1
    discovery_time[nod] = time
    low[nod] = time
    time += 1
    copii = 0

    for vecin in lista[nod]:
        if vizitat[vecin] == 0:
            parent[vecin] = nod
            copii += 1
            DFS(vecin)
            low[nod] = min(low[nod], low[vecin])
            if parent[nod] == -1 and copii > 1:
                puncte_critice[nod] = True
            if low[vecin] >= discovery_time[nod] and parent[nod] != -1:
                puncte_critice[nod] = True
        elif vecin != parent[nod]:
            low[nod] = min(low[nod], discovery_time[vecin])


for nod in range(1, n + 1):
    if vizitat[nod] == 0:
        DFS(nod)
if len(puncte_critice) == 0:
    print("Nu exista puncte critice.")
else:
    print("Puncte critice:")
    for nod in range(1, n + 1):
        if puncte_critice[nod]:
            print(nod, end = " ")


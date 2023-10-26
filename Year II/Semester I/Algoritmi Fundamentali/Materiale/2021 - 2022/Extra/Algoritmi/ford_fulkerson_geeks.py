# Algoritmul lui Ford-Fulkerson pentru determinarea fluxului maxim.

f = open("ponderi.in")
line = f.readline()
v = line.split()
n = int(v[0])
m = int(v[1])

lista = [[0 for j in range(n + 1)] for i in range(n + 1)]

for i in range(0, m):
    line = f.readline()
    v = line.split()
    x = v[0]
    y = v[1]
    cost = int(v[2])
    if x == "s":
        x = 0
    if x == "t":
        x = n - 1
    if y == "s":
        y = 0
    if y == "t":
        y = n - 1
    x = int(x)
    y = int(y)
    lista[x][y] = cost
f.close()
print(lista)


def BFS(s, t, parent):
    global lista
    vizitat = [False] * (n + 1)
    coada = []
    coada.append(s)
    vizitat[s] = True

    while len(coada):
        nod = coada.pop(0)
        for vecin, cost in enumerate(lista[nod]):
            if vizitat[vecin] == False and cost > 0:
                coada.append(vecin)
                vizitat[vecin] = True
                parent[vecin] = nod
                if vecin == t:
                    return True

    return False


def FordFulkerson(source, sink):
    global lista
    parent = [-1] * (n + 1)
    max_flow = 0
    while BFS(source, sink, parent):
        path_flow = float("infinity")
        s = sink
        while s != source:
            path_flow = min(path_flow, lista[parent[s]][s])
            s = parent[s]

        max_flow += path_flow
        v = sink
        while v != source:
            u = parent[v]
            lista[u][v] -= path_flow
            lista[v][u] += path_flow
            v = parent[v]

    return max_flow


source = 0
sink = n - 1
print(FordFulkerson(source, sink))

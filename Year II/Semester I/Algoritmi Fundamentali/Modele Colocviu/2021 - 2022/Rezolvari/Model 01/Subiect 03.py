# Propuneți un algoritm bazat pe algoritmul Ford-Fulkerson / Edmonds Karp pentru rezolvarea
# următoarei probleme.
# Într-un restaurant sunt n mese numerotate 1,...,n sunt și m ospătari numerotați 1,..., m.
# Proprietarul restaurantului urmează să aibă un eveniment în restaurant și dorește să repartizeze
# fiecărui ospătar mesele de care trebuie să se ocupe. El întreabă pe fiecare ospătar la ce mese ar
# vrea să servească, altfel că pentru fiecare ospătar j știe lista meselor pe care le preferă.
# Proprietarul ar vrea ca la fiecare masă să fie exact k ospătari și un ospătar să servească la cel
# mult p mese și ar vrea să respecte și preferințele ospătarilor legate de mese.
# Scrieți un program care, dacă este posibilă o distribuție a ospătarilor la mese care să respecte
# dorințele proprietarului, cu cel mult o excepție și anume o masă la care să fie doar k-1 ospătari,
# să afișeze o astfel de distribuție sub forma prezentată în exemplul de mai jos (perechi masa
# ospătar). Altfel se va afișa mesajul “imposibil”
# Datele despre restaurant și opțiunile ospătarilor se vor citi dintr-un fișier cu următoarea
# structură:
# - pe prima linie sunt numerele naturale n, m, k, p


f = open("restarurant.in")
line = f.readline()
v = line.split()
n = int(v[0])
m = int(v[1])
k = int(v[2])
p = int(v[2])


s = n + m + 1
t = n + m + 2
muchii = 0
g = open("creare_retea.in", mode='w')
g.write(f"{n + m + 2} { n + m + m}\n")
for i in range(1, n + 1):
    g.write(f"{s} {i} {k}\n")

for i in range(1, m + 1):
    g.write(f"{i + n} {t} {p}\n")


for i in range(m):
    line = f.readline()
    v = line.split()
    vect = [int(x) for x in v]
    for j in range(1, vect[0] + 1):
        g.write(f"{vect[j]} {i + n + 1} {1}\n")


g.close()
f.close()
initial_n = n
initial_m = m


def create_graph():
    f = open("creare_retea.in")

    line = f.readline()
    v = line.split()
    n = int(v[0])
    m = int(v[1])
    graph = [[0 for i in range(n + 1)] for j in range(n + 1)]
    initial_graph = [[0 for i in range(n + 1)] for j in range(n + 1)]
    for i in range(m):
        line = f.readline()
        v = line.split()
        x = int(v[0])
        y = int(v[1])
        cost = int(v[2])
        graph[x][y] = cost
        initial_graph[x][y] = cost
    f.close()

    # for i in range(1, n + 1):
    #     for j in range (1, n + 1):
    #         print(f"{graph[i][j]} ", end=" ")
    #     print()

    return graph, initial_graph, n


graph, initial_graph, n = create_graph()


def BFS(s, t, graph, parent):
    vizitat = [False] * (n + 1)
    coada = []
    coada.append(s)
    vizitat[s] = True

    while len(coada):
        nod = coada.pop(0)
        for vecin, cost in enumerate(graph[nod]):
            if vizitat[vecin] == False and cost > 0:
                coada.append(vecin)
                vizitat[vecin] = True
                parent[vecin] = nod
                if vecin == t:
                    return True

    return False


def FordFulkerson(source, sink):
    global graph
    parent = [-1] * (n + 1)
    max_flow = 0
    while BFS(source, sink, graph, parent):
        path_flow = float("infinity")
        s = sink
        while s != source:
            path_flow = min(path_flow, graph[parent[s]][s])
            s = parent[s]

        max_flow += path_flow
        v = sink
        while v != source:
            u = parent[v]
            graph[u][v] -= path_flow
            graph[v][u] += path_flow
            v = parent[v]

    return max_flow


source = n - 1
sink = n
max_flow = FordFulkerson(source, sink)
print(max_flow)
# for i in range(1, n + 1):
#     for j in range (1, n + 1):
#         print(f"{graph[i][j]} ", end=" ")
#     print()
# for i in range(1, n):
for i in range(1, n):
    for j in range(1, n):
        if i < j and j > initial_n:
            if initial_graph[i][j] != 0 and graph[i][j] == 0:
                print(f"{i} {j - initial_n}")
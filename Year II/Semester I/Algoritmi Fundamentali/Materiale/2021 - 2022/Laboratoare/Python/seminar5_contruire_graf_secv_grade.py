
f = open("seminar6.in")
line = f.readline()
v = line.split()
n = int(v[0])


line = f.readline()
v = line.split()
intrare = []
for x in v:
    y = int(x)
    intrare.append(y)
line = f.readline()


v = line.split()
iesire = []
for x in v:
    y = int(x)
    iesire.append(y)

f.close()


# sursa = 2n + 1
# destinatie = 2n + 2
# x1 .. xn = 1 .. n
# y1 .. yn = n+1 .. 2n
s = 2 * n + 1
t = 2 *  n +  2

g = open("creare_retea.in", mode='w')
# (extremitate1, extremitate2, capacitate)

# sxi de capacitate = iesire[i]
g.write(f"{2 * n + 2}\n")

for i in range(1, n + 1):
    g.write(f"{s} {i} {iesire[i - 1]}\n")

for i in range(n + 1, 2 * n + 1):
    g.write(f"{i} {t} {intrare[i - n - 1]}\n")

for i in range(1, n + 1):
    for j in range(n + 1, 2 * n + 1):
        if i + n != j:
            g.write(f"{i} {j} {1}\n")
g.close()

def create_graph():
    f = open("creare_retea.in")

    line = f.readline()
    v = line.split()
    n = int(v[0])
    graph = [[0 for i in range(n + 1)] for j in range(n + 1)]
    for i in range(1, 2 * n + 1):
        line = f.readline()
        v = line.split()
        x = int(v[0])
        y = int(v[1])
        cost = int(v[2])
        graph[x][y] = cost
    f.close()

    for i in range(n + 1):
        for j in range (n + 1):
            print(f"{graph[i][j]} ", end=" ")
        print()

    return graph, 2 * n


graph, n = create_graph()


from collections import defaultdict

class Graph:
    def __init__(self, graph):
        self.graph = graph
        self.row = len(graph)

    def BFS(self, s, t, parent):
        visited = [False] * (self.row)

        queue = []

        queue.append(s)
        visited[s] = True

        while queue:
            u = queue.pop(0)

            for ind, val in enumerate(self.graph[u]):
                if visited[ind] == False and val > 0:
                    queue.append(ind)
                    visited[ind] = True
                    parent[ind] = u
                    if ind == t:
                        return True

        return False

    def ford_fulkerson(self, source, sink):
        parent = [-1] * (self.row)

        max_flow = 0

        while self.BFS(source, sink, parent):
            path_flow = float("Inf")
            s = sink
            while s != source:
                path_flow = min(path_flow, self.graph[parent[s]][s])
                s = parent[s]

            max_flow += path_flow

            v = sink
            while v != source:
                u = parent[v]
                self.graph[u][v] -= path_flow
                self.graph[v][u] += path_flow
                v = parent[v]
        return max_flow

    def afis(self):
        global n
        for i in range(n+1):
            for j in range(n+1):
                print(self.graph[j][i], end = " ")
            print()

# se face ford fulkerson
g = Graph(graph)
source = 0
sink = n
print("The maximum possible flow is %d " % g.ford_fulkerson(source, sink))
g.afis()


def afis(sursa, matrice_flux):
    suma = 0
    for i in range(1, n + 1):
        suma = suma + matrice_flux[sursa][i]
    h = open("muchii.in", "w")

    if suma != sum(iesire):
        h.write("Nu exista!\n")
    else:
        for i in range(1, n + 1):
            for j in range(n + 1, 2 * n + 1):
                if matrice_flux[i][j] != 0:
                        h.write(f"{i} {j - n} ")
            h.write('\n')
    h.close()


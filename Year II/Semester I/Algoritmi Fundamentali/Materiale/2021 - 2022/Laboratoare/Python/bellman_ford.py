class Graph:
    def __init__(self, nodes):
        self.nodes = nodes
        self.graph = []

    def add_edge(self, x, y, cost):
        self.graph.append([x, y, cost])

    def printArr(self, dist):
        print("Node Distance from Source")
        for i in range(self.nodes):
            print("{0}\t\t{1}".format(i, dist[i]))

    def BellmanFord(self, src):
        dist = [float("Inf")] * (self.nodes + 1)
        dist[src] = 0

        for _ in range(self.nodes - 1):
            for u, v, w in self.graph:
                if dist[u] != float("Inf") and dist[u] + w < dist[v]:
                    dist[v] = dist[u] + w

        for u, v, w in self.graph:
            if dist[u] != float("Inf") and dist[u] + w < dist[v]:
                print("Graph contains negative weight cycle")
                return

        self.printArr(dist)

f = open("bellman_ford.in")
line = f.readline()
v = line.split()
n = int(v[0])
m = int(v[1])

g = Graph(n)
for i in range(m):
    line = f.readline()
    v = line.split()
    x = int(v[0])
    y = int(v[1])
    cost = int(v[2])
    g.add_edge(x, y, cost)

start = int(input("Introduceti nodul de start: "))
g.BellmanFord(start)
f.close()
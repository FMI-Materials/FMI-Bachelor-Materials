from collections import defaultdict

class Graph:
    def __init__(self, nodes):
        self.graph = defaultdict(list)
        self.nodes = nodes

    def add_edge(self, x, y):
        self.graph[x].append(y)

    def topological_sort_util(self, start, visited, stack):
        visited[start] = True

        for i in self.graph[start]:
            if visited[i] == False:
                self.topological_sort_util(i, visited, stack)

        stack.insert(0, start)

    def topological_sort(self):
        visited = [False] * (self.nodes + 1)
        stack = []

        for i in range(self.nodes + 1):
            if visited[i] == False:
                self.topological_sort_util(i, visited, stack)

        print(stack)

f = open("kosaraju.in")
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
    g.add_edge(x,y)
f.close()
print("topological Sort: ")
g.topological_sort()
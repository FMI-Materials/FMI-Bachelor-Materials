# f = open("graf_kruskal.in")
# line = f.readline()
# v = line.split()
#
# nrNoduri = int(v[0])
# nrMuchii = int(v[1])
#
# def reprezentat(nod):
#     global tata
#     if tata[nod] == 0:
#         return nod
#     tata[nod] = reprezentat(tata[nod])
#     return tata[nod]
#
# def reuniune(x, y):
#     global tata, h
#     reprezentant_x = reprezentat(x)
#     reprezentant_y = reprezentat(y)
#
#     if h[reprezentant_x] > h[reprezentant_y]:
#         tata[reprezentant_y] = reprezentant_x
#     else:
#         tata[reprezentant_x] = reprezentant_y
#         if h[reprezentant_y] == h[reprezentant_x]:
#             h[reprezentant_y] = h[reprezentant_y] + 1
#
# def citire_graf_costuri(noduri , muchii):
#     lista = []
#
#     for i in range(muchii):
#         line=f.readline()
#         v=line.split()
#         x = int(v[0])
#         y = int(v[1])
#         cost = int(v[2])
#         t = (x, y, cost)
#         lista.append(t)
#     return lista
#
# muchii = citire_graf_costuri(nrNoduri, nrMuchii)
# f.close()
# print(muchii)
#
# tata = [0] * (nrNoduri + 1)
# h = [0] * (nrNoduri + 1)
#
# muchii = sorted(muchii, key = lambda e: e[2])
#
# nr_muchii_arbore = 0
# cost_total = 0
#
# for m in muchii:
#     if reprezentat(m[0]) != reprezentat(m[1]):
#         print(m[0], m[1])
#         reuniune(m[0],m[1])
#         cost_total = cost_total + m[2]
#         nr_muchii_arbore = nr_muchii_arbore + 1
#         if nr_muchii_arbore == nrNoduri - 1:
#             break
#
# print("cost =", cost_total)
# print("arbore de paduri disjuncte:", tata[1:])
# print("vector de inaltimi: " , h[1:])

from collections import defaultdict


# Class to represent a graph


class Graph:

    def __init__(self, nodes):
        self.nodes = nodes  # No. of vertices
        self.graph = []  # default dictionary
        # to store graph

    # function to add an edge to graph
    def add_edge(self, u, v, w):
        self.graph.append([u, v, w])

    # A utility function to find set of an element i
    # (uses path compression technique)
    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])

    # A function that does union of two sets of x and y
    # (uses union by rank)
    def union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)

        # Attach smaller rank tree under root of
        # high rank tree (Union by Rank)
        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot

        # If ranks are same, then make one as root
        # and increment its rank by one
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    # The main function to construct MST using Kruskal's
    # algorithm
    def KruskalMST(self):

        result = []  # This will store the resultant MST

        # An index variable, used for sorted edges
        i = 0

        # An index variable, used for result[]
        e = 0

        # Step 1:  Sort all the edges in
        # non-decreasing order of their
        # weight.  If we are not allowed to change the
        # given graph, we can create a copy of graph
        self.graph = sorted(self.graph, key=lambda item: item[2])

        parent = []
        rank = []

        # Create V subsets with single elements
        for node in range(self.nodes):
            parent.append(node)
            rank.append(0)

        # Number of edges to be taken is equal to V-1
        while e < self.nodes - 1:

            # Step 2: Pick the smallest edge and increment
            # the index for next iteration
            u, v, w = self.graph[i]
            i = i + 1
            x = self.find(parent, u)
            y = self.find(parent, v)

            # If including this edge does't
            #  cause cycle, include it in result
            #  and increment the indexof result
            # for next edge
            if x != y:
                e = e + 1
                result.append([u, v, w])
                self.union(parent, rank, x, y)
            # Else discard the edge

        minimumCost = 0
        print("Edges in the constructed MST")
        for u, v, weight in result:
            minimumCost += weight
            print("%d -- %d == %d" % (u, v, weight))
        print("Minimum Spanning Tree", minimumCost)

f = open("kruskal.in")
# line = f.readline()
# v = line.split()
# n = int(v[0])
# m = int(v[1])
# g = Graph(n + 1)
# for i in range(m):
#     line = f.readline()
#     v = line.split()
#     x = int(v[0])
#     y = int(v[1])
#     cost = int(v[2])
#     g.add_edge(x, y, cost)
g = Graph(4)
g.add_edge(0, 1, 10)
g.add_edge(0, 2, 6)
g.add_edge(0, 3, 5)
g.add_edge(1, 3, 15)
g.add_edge(2, 3, 4)


# Function call
g.KruskalMST()

# Conectare cu cost minim a nodurilor de mai multe surse.
import math
def getEuclideanDistance(node1, node2, coords):

    res1 = (coords[node1][0] - coords[node2][0]) ** 2
    res2 = (coords[node1][1] - coords[node2][1]) ** 2
    return math.sqrt(res1 + res2)


def citire(orientat: bool = False):
    f = open("retea2.in")
    line = f.readline()
    v = line.split()
    nrOfPowerStations = int(v[0])
    nrOfBuildings = int(v[1])
    nrOfEdges = int(v[2])

    adjacentList = [[] for _ in range(nrOfPowerStations + nrOfBuildings)]
    edges = []
    coords = []

    for i in range(nrOfPowerStations +  nrOfBuildings):
        x, y = [int(coord) for coord in f.readline().split()]
        coords.append((x, y))

    for i in range(nrOfEdges):
        line = f.readline()
        v = line.split()
        nod1 = int(v[0])
        nod2 = int(v[1])
        distance = getEuclideanDistance(nod1 - 1, nod2 - 1, coords)
        edges.append((nod1 - 1, nod2 - 1, distance))
        adjacentList[nod1 - 1].append([nod2 - 1, distance])

        if not orientat:
            adjacentList[nod2 - 1].append([nod1 - 1, distance])

    edges.sort(key = lambda e: e[2])
    f.close()

    return adjacentList, edges, nrOfPowerStations, nrOfBuildings


def reprezentant(node):
    global parent
    if parent[node] == -1:
        return node

    parent[node] = reprezentant(parent[node])
    return parent[node]


def intersectie(fstNode, sndNode):
    global n, parent, height
    rep1 = reprezentant(fstNode)
    rep2 = reprezentant(sndNode)

    height1 = height[rep1]
    height2 = height[rep2]

    if height1 > height2:
        parent[rep2] = rep1
        return

    parent[rep1] = rep2
    if height[rep1] == height[rep2]:
        height[rep2] += 1
    return


def printMST(mst):
    global words
    print("MSTree:", [(node1, node2, weight) for (node1, node2, weight) in mst])
    print("Weight:", sum(list(map(lambda x: x[2], mst))))


oriented = False
adjacentList, edges, n, m = citire(oriented)

height = [0 for _ in range(len(adjacentList))]
parent = [-1 for _ in range(len(adjacentList))]
minimumSpanningTree = []
countEdgesInMST = 0

for i in range(n):
    if i != 0:
        parent[i] = 0  # all the power stations are in the same component!
    height[i] = 1

for edge in edges:
    fstNode, sndNode = edge[0], edge[1]

    if reprezentant(fstNode) != reprezentant(sndNode):
        intersectie(fstNode, sndNode)
        minimumSpanningTree.append(edge)
        countEdgesInMST += 1

    if countEdgesInMST == m:  # MST will have m edges now
        break


printMST(minimumSpanningTree)
# Algoritmul de determinare a second best MST.

import copy
import math

def getEdges(file, oriented: bool = False):
    f = open(file)
    line = f.readline()
    v = line.split()
    n = int(v[0])
    m = int(v[1])
    adjacentList = [[] for i in range(n)]
    edges = []

    for i in range(m):
        line = f.readline()
        v = line.split()
        x = int(v[0])
        y = int(v[1])
        cost = int(v[2])
        edges.append((x - 1, y - 1, cost))
        adjacentList[x - 1].append([y - 1, cost])

        if not oriented:
            adjacentList[y - 1].append([x - 1, cost])

    return adjacentList, edges


def printList(adjacentList: list):
    for i in range(len(adjacentList)):
        result = [(node + 1, weight) for (node, weight) in adjacentList[i]]
        print(str(i + 1) + ": " + str(result))


def reprezentant(nod):
    global parent
    if parent[nod] == -1:
        return nod

    parent[nod] = reprezentant(parent[nod])
    return parent[nod]


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
    print("MSTree:", [(node1 + 1, node2 + 1, weight) for (node1, node2, weight) in mst])
    print("Weight:", sum(list(map(lambda x: x[2], mst))))


def DFS(root):
    global n, visited, adjTree, dfPath, check, parentTree
    if check:
        return
    visited[root] = 1
    for neighbour, weight in adjTree[root]:
        if not visited[neighbour]:
            parentTree[neighbour] = root
            dfPath.append((root, neighbour, weight))
            DFS(neighbour)

            if check:
                return
            dfPath.pop()

        elif parentTree[root] != neighbour:
            dfPath.append((root, neighbour, weight))
            check = True
            return


def getMaxEdge(dfPath, newEdge):
    maxEdge = [-1, -1, -1]
    for edge in dfPath:
        edges = (edge[0], edge[1])
        if edge[2] > maxEdge[2]:
            if newEdge[0] in edges and newEdge[1] in edges:
                continue
            maxEdge = edge

    return maxEdge


oriented = False
adjacentList, edges = getEdges("secondBest.in", oriented)
n = len(adjacentList)
m = len(edges)

parent = [-1 for i in range(n)]
height = [0 for j in range(n)]

mst = []
countEdgesMST = 0

edges.sort(key = lambda e: e[2])
remainingEdges = copy.deepcopy(edges)

for edge in edges:
    nod1, nod2 = edge[0], edge[1]

    if reprezentant(nod1) != reprezentant(nod2):
        intersectie(nod1, nod2)
        mst.append(edge)
        countEdgesMST += 1
        remainingEdges.remove(edge)

    if countEdgesMST == n - 1:
        break

print("Best Tree")
printMST(mst)

adjTree = [[] for i in range(n)]
for edge in mst:
    nod1, nod2, cost = edge[0], edge[1], edge[2]
    adjTree[nod1].append((nod2, cost))

    if not oriented:
        adjTree[nod2].append((nod1, cost))

lastEdgeIndex = edges.index(mst[-1])
secondMST = [None, None, math.inf]

for i in range(len(remainingEdges)):
    parentTree = [-1 for i in range(n)]
    visited = [0 for j in range(n)]
    dfPath = []
    check = False
    newEdge = remainingEdges[i]
    nod1, nod2, cost = newEdge[0], newEdge[1], newEdge[2]
    mst.append(newEdge)
    adjTree[nod1].append([nod2, cost])
    if not oriented:
        adjTree[nod2].append([nod1, cost])

    DFS(nod1)
    maxEdge = getMaxEdge(dfPath, newEdge)
    difference = newEdge[2] - maxEdge[2]
    minDifference = secondMST[2]

    if difference < minDifference:
        secondMST[2] = difference
        secondMST[0] = newEdge
        secondMST[1] = maxEdge

    mst.pop()
    adjTree[nod1].pop()
    if not oriented:
        adjTree[nod2].pop()

secondBest = copy.deepcopy(mst)
secondBest.append(secondMST[0])
secondBest.append(secondMST[1])
print("Second Best Tree:")
printMST(secondBest)

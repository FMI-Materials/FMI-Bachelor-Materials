# Clustering
# Distanta intre doua cuvinte.

def Levenshtein(word1, word2):
    if len(word2) == 0:
        return len(word1)
    elif len(word1) == 0:
        return len(word2)
    elif word1[0] == word2[0]:
        return Levenshtein(word1[1:], word2[1:])
    else:
        return 1 + min(Levenshtein(word1, word2[1:]), Levenshtein(word1[1:], word2), Levenshtein(word1[1:], word2[1:]))


def getWords(file):
    f = open(file)
    words = f.read().replace("\n", " ").split()
    f.close()
    return words


def getSortedEdges(words):
    lista = []

    for i in range(len(words) - 1):
        for j in range(i + 1, len(words)):
            dist = Levenshtein(words[i], words[j])
            lista.append((i, j, dist))

    lista.sort(key = lambda e: e[2])
    return lista


def reprezentant(nod):
    global parent
    if parent[nod] == -1:
        return nod

    parent[nod] = reprezentant(parent[nod])
    return parent[nod]


def intersectie(nod1, nod2):
    global n, parent, height, clusters
    rep1 = reprezentant(nod1)
    rep2 = reprezentant(nod2)

    height1 = height[rep1]
    height2 = height[rep2]

    if height1 > height2:
        parent[rep2] = rep1
        clusters[rep1] += clusters[rep2]
        clusters[rep2].clear()
        return

    parent[rep1] = rep2
    clusters[rep2] += clusters[rep1]
    clusters[rep1].clear()

    if height[rep1] == height[rep2]:
        height[rep2] += 1
    return


def printMST(mst):
    global words
    print("MSTree:", [(node1, node2, weight) for (node1, node2, weight) in mst])
    print("Weight:", sum(list(map(lambda x: x[2], mst))))


def getSeparationDegree(edges, index):
    for i in range(index + 1, len(edges)):
        fstNode, sndNode = edges[i][0], edges[i][1]

        if reprezentant(fstNode) != reprezentant(sndNode):
            sepDegree = edges[i][2]
            return sepDegree
    return 0


k = 3
words = getWords("cuvinte.in")
edges = getSortedEdges(words)
n = len(words)

parent = [-1 for _ in range(n)]
height = [0 for _ in range(n)]
clusters = [[i] for i in range(n)]

minimumSpanningTree = []
countEgdesInMST = 0

for edge in edges:
    fstNode, sndNode = edge[0], edge[1]

    if reprezentant(fstNode) != reprezentant(sndNode):
        intersectie(fstNode, sndNode)
        minimumSpanningTree.append(edge)
        countEgdesInMST += 1

    if countEgdesInMST == n - k:
        break

separationDegree = getSeparationDegree(edges, countEgdesInMST)

for cluster in clusters:
    if len(cluster) > 0:
        for elem in cluster:
            print(words[elem], end = " ")
        print()

print("Separation Degree: ", separationDegree)
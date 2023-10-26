# Algoritmul lui Floyd-Warshall pentru a determina drumul minim intre oricare doua noduri
# O(n^3)

f = open("ponderi.in")
line = f.readline()
v = line.split()
n = int(v[0])
m = int(v[1])


def create_distance_matrix(n, m):
    l = []
    for i in range(n + 1):
        line = []
        for j in range(n + 1):
            line.append(float("infinity"))
        l.append(line)
    for i in range(n + 1):
        l[i][i] = 0
    for i in range(m):
        line = f.readline()
        v = line.split()
        x, y, cost = v
        x = int(x)
        y = int(y)
        cost = int(cost)
        l[x][y] = min(l[x][y], cost)
    return l


matrice = create_distance_matrix(n, m)
f.close()


def sol(dist):
    for p in range(1, n + 1):
        for q in range(1, n + 1):
            if dist[p][q] == float("infinity"):
                print(float("infinity"), end = " ")
            else:
                print(dist[p][q], end = " ")
        print()


def floyd_warshall(matrice):
    dist = list(map(lambda p: list(map(lambda q: q, p)), matrice))
    for r in range(1, n + 1):
        for p in range(1, n + 1):
            for q in range(1, n + 1):
                dist[p][q] = min(dist[p][q], dist[p][r] + dist[r][q])
    sol(dist)


floyd_warshall(matrice)
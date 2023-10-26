f = open("floyd_warshall.in")
line = f.readline()
v = line.split()
n = int(v[0])
m = int(v[1])


def create_distance_matrix(n, m):
    l = []
    for i in range(n + 1):
        linie = []
        for j in range(n + 1):
            linie.append(float("Inf"))
        l.append(linie)
    for i in range(n + 1):
        l[i][i] = 0
    for i in range(m):
        line = f.readline()
        v = line.split()
        x = int(v[0])
        y = int(v[1])
        cost = int(v[2])
        l[x][y] = min(l[x][y], cost)

    return l
matrice = create_distance_matrix(n, m)
for p in range(1, n + 1):
    for q in range(1, n + 1):
        if matrice[p][q] == float("Inf"):
            print(float("Inf"), end=" ")
        else:
            print(matrice[p][q], end=" ")
    print()
print()
def sol(dist):
    for p in range(1, n + 1):
        for q in range(1, n + 1):
            if dist[p][q] == float("Inf"):
                print(float("Inf"), end = " ")
            else:
                print(dist[p][q], end = " ")
        print("")


def floyd_warshall(matrice):
    dist = list(map(lambda p: list(map(lambda q: q, p)), matrice))
    for r in range(1, n + 1):
        for p in range(1, n + 1):
            for q in range(1, n + 1):
                dist[p][q] = min(dist[p][q], dist[p][r] + dist[r][q])
    sol(dist)


floyd_warshall(matrice)
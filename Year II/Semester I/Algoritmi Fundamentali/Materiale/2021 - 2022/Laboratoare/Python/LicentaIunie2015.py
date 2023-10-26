# . Se dă o matrice n*m (n,m <= 1000), cu p <= 100 puncte marcate cu 1 (restul valorilor din
# matrice vor fi 0). Distanța dintre 2 puncte ale matricei se măsoară în locații străbătute mergând
# pe orizontală și pe verticală între cele 2 puncte (distanța Manhattan). Se dă o mulțime M de q
# puncte din matrice (q <= 1000000). Să se calculeze cât mai eficient pentru fiecare dintre cele q
# puncte date, care este cea mai apropiată locație marcată cu 1 din matrice. (Licență iunie 2015)
f = open("input.in")

line = f.readline()
v = line.split()

n = int(v[0])
m = int(v[1])

final = []

def citire_matrice(n, m):
    matrice = []
    for i in range(n):
        ma = []
        line = f.readline()
        v = line.split()
        for j in range(m):
            ma.append(int(v[j]))
            if int(v[j]) == 1:
                final.append((i+1,j+1))
                ma.append(-1)
            else:
                ma.append(0)
        matrice.append(ma)
    return matrice

matrice = citire_matrice(n,m)


start = []
for x in f.readlines():
    v = x.split()
    start.append((int(v[0]), int(v[1])))
f.close()

dx = [0, 0, 1, -1]
dy = [1, -1, 0, 0]

def inMatrice(l, c):
    if l < 0 or c < 0 or l >= n or c >= m:
        return False
    if (l+1,c+1) in final:
        return False
    return True


def lee(startx,starty,matrice):
    from collections import deque
    coada = deque([])

    matrice[startx][starty] = 1
    coada.append((startx,starty))

    while len(coada)>0:
        pair = coada.popleft()
        x = pair[0]
        y = pair[1]

        for directie in range(0,4):
            xn = x + dx[directie]
            yn = y + dy[directie]

            if inMatrice(xn,yn) == True and matrice[xn][yn] < 1:
                matrice[xn][yn] = matrice[x][y] + 1
                coada.append((xn,yn))
            elif (xn + 1, yn + 1) in final:
                print(matrice[x][y], " [", xn + 1, ","
                                                   "", yn + 1, "]")
                coada = deque([])
                break

for tuple in start:
    copy=matrice
    lee(tuple[0]-1, tuple[1]-1, copy)


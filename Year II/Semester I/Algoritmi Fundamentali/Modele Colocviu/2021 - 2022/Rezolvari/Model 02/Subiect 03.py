# Algoritmul lui Edmonds Karp pentru determinarea
# fluxului maxim intr-un graf orientat cu ponderi
# ce reprezinta capacitatea maxima a muchiei

def matriceCapacitate(fisier):
    global n, m

    f = open(fisier, "r")

    n, m = [int(x) for x in f.readline().split()]

    lista = []
    matrice = [[0] * n for _ in range(n)]

    for i in range(m):
        aux = [int(x) for x in f.readline().split()]
        lista.append(tuple(aux))

    for muchie in lista:
        # calculam distanta pentru fiecare element al matricei
        matrice[muchie[0] - 1][muchie[1] - 1] = muchie[2]

    return matrice

# algoritmul lui edmonds karp se
# foloseste de bfs pentru a alege drumul minim

def bfs():
    global matrice, s, t, n, tata

    vizitat = [False] * n
    queue = []
    queue.append(s)

    vizitat[s] = True

    while queue:
        u = queue.pop(0)
        for nod, val in enumerate(matrice[u]):
            if vizitat[nod] == False and val > 0:
                queue.append(nod)
                vizitat[nod] = True
                tata[nod] = u

    return True if vizitat[t] else False

def edmonds(matrice):
    global s, t, n, tata

    fluxMaxim = 0

    while bfs():
        flux = inf
        nod = t
        while nod != s:
            flux = min(flux, matrice[tata[nod]][nod])
            nod = tata[nod]

        fluxMaxim = fluxMaxim + flux

        v = t
        while v != s:
            u = tata[v]

            # arc direct
            matrice[u][v] = matrice[u][v] - flux

            # arc invers
            matrice[v][u] = matrice[v][u] + flux
            v = tata[v]

    return fluxMaxim

matrice = matriceCapacitate("restaurant.in")
inf = float('inf')

s = 0       # s
t = n - 1   # t
tata = [-1] * (n)

flux = edmonds(matrice)

print(flux)
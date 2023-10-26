# Algoritmul lui Bellman-Ford pentru determinarea distantelor de la un nod la celelalte noduri intr-un graf cu ponderi negative.
# O(n * m)
# 9 14
# 9 1 4
# 1 2 8
# 2 3 7
# 3 4 9
# 4 5 10
# 5 6 2
# 6 7 1
# 7 9 8
# 7 8 7
# 6 8 6
# 8 2 2
# 5 2 4
# 7 1 11
# 5 3 14
f = open("ponderi_negative.in")
line = f.readline()
v = line.split()
n = int(v[0])
m = int(v[1])
lista = []


for i in range(m):
    line = f.readline()
    v = line.split()
    x = int(v[0])
    y = int(v[1])
    cost = int(v[2])
    lista.append((x, y, cost))


def BellmanFord(nod, lista):
    distante = [float("infinity")] * (n + 1)
    distante[nod] = 0

    for cnt in range(1, n + 1):
        for x, y, cost in lista:
            if distante[x] != float("infinity") and distante[x] + cost < distante[y]:
                distante[y] = distante[x] + cost

    for x, y, cost in lista:
        if distante[x] != float("infinity") and distante[x] + cost < distante[y]:
            print("Graful contine ciclu de cost negativ")

    return distante


start = 1
print(BellmanFord(start, lista))
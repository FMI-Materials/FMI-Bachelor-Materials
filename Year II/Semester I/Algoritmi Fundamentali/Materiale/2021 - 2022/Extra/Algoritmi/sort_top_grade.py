# Sortare topologica folosind BFS si gradele interne - calculeaza si distantele .
from queue import Queue
f = open("ponderi_negative.in")
line = f.readline()
v = line.split()
n = int(v[0])
m = int(v[1])
grad = [0] * (n + 1)

lista = {}
for i in range(1, n + 1):
    lista[i] = []

for i in range(1, m + 1):
    line = f.readline()
    v = line.split()
    x = int(v[0])
    y = int(v[1])
    cost = int(v[2])
    lista[x].append((y, cost))
    grad[y] += 1
f.close()
sortate = []
coada = Queue()
for i in range(1, n + 1):
    if grad[i] == 0:
        coada.put(i)
        sortate.append(i)

start = int(input("Nodul de start pt calcularea distantei: "))
dist = [float("infinity") for x in range(n + 1)]
dist[start] = 0

while not coada.empty():
    nod = coada.get()
    for (vecin, cost) in lista[nod]:
        grad[vecin] -= 1
        if grad[vecin] == 0:
            coada.put(vecin)
            sortate.append(vecin)
        if dist[vecin] > dist[nod] + cost:
            dist[vecin] = dist[nod] + cost

print(f"Sortare topologica: {sortate}")
print(f"Distante: {dist[1:]}")

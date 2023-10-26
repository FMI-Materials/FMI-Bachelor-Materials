# DAG - Directed Actclic Graph - cel mai scurt drum.
from queue import Queue

f = open("DAG.in")
line = f.readline()
v = line.split()
n = int(v[0])
line = f.readline()
cost_muchie = [int(x) for x in line.split()]

lista = [[] for i in range(n + 2)]
grad_intern = [0 for i in range(n + 2)]
grad_extern = [0 for i in range(n + 2)]

line = f.readline()
v = line.split()
m = int(v[0])

for i in range(m):
    line = f.readline()
    v = line.split()
    x = int(v[0])
    y = int(v[1])
    cost = cost_muchie[x - 1]
    lista[x].append((y, cost))
    grad_intern[y] = grad_intern[y] + 1
    grad_extern[x] = grad_extern[x] + 1

for i in range(1, n + 1):
    if grad_intern[i] == 0:
        lista[0].append((i, 0))

nod_terminal = n + 1
for i in range(1, n + 1):
    if grad_extern[i] == 0:
        lista[i].append((nod_terminal, cost_muchie[i - 1]))


def sortare_topologica():
    coada = Queue(maxsize = n + 2)

    for i in range(0, n + 2):
        if grad_intern[i] == 0:
            coada.put(i)
    sortate = []
    while not coada.empty():
        nod = coada.get()
        sortate.append(nod)
        for vecin in lista[nod]:
            grad_intern[vecin[0]] = grad_intern[vecin[0]] - 1
            if grad_intern[vecin[0]] == 0:
                coada.put(vecin[0])
    return sortate


def det_drum_maxim(start):
    d[start] = 0
    sortate = sortare_topologica()
    for nod in sortate:
        for (vecin, cost) in lista[nod]:
            if d[nod] + cost > d[vecin]:
                d[vecin] = d[nod] + cost
                tata[vecin] = nod

f.close()

tata = [0 for i in range(n + 2)]
d = [-9999999 for i in range(n + 2)]
det_drum_maxim(0)

nod = nod_terminal
reconstruire = []
while nod != 0:
    if nod != nod_terminal and nod != 0:
        reconstruire.append(nod)
    nod = tata[nod]

reconstruire.reverse()
print(f"Timp minim: {d[n] + cost_muchie[n - 1]}")
print(f"Activitati critice: {reconstruire}")

print("\n")
for i in range(1,n+1):
    print(f"{i}: {d[i]} {d[i]+cost_muchie[i-1]}")

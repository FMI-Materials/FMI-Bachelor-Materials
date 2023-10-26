# Sortare topologica

f = open("graf1.in")
line = f.readline()
v = line.split()
n = int(v[0])
m = int(v[1])
print(n, m)
lista = {}
for i in range(1, n + 1):
    lista[i] = []

for i in range(1, m + 1):
    line = f.readline()
    v = line.split()
    x = int(v[0])
    y = int(v[1])
    lista[x].append(y)
f.close()

vizitat = [0] * (n + 1)
stiva = []


def DFS(nod):
    vizitat[nod] = 1
    for vecin in lista[nod]:
        if vizitat[vecin] == 0:
            DFS(vecin)
    stiva.append(nod)


for i in range(1, n + 1):
    if vizitat[i] == 0:
        DFS(i)

sortate = []
for i in range(len(stiva) - 1, -1, -1):
    sortate.append(stiva[i])

print(sortate)




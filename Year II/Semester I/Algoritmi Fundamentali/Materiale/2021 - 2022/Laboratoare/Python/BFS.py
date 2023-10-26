import queue

f = open("graf.in")
line = f.readline()
v = line.split()

nrNoduri = int(v[0])
nrMuchii = int(v[1])

def citire_matrice_liste(noduri,muchii,orientat):
    l = {}
    for i in range(1, noduri + 1):
        l[i] = []

    for i in range(muchii):
        line = f.readline()
        v = line.split()
        if orientat:
            l[int(v[0])].append(int(v[1]))
        else:
            l[int(v[0])].append(int(v[1]))
            l[int(v[1])].append(int(v[0]))
    return l

lista = citire_matrice_liste(nrNoduri,nrMuchii,0)
f.close()

vizitat = [0] * (nrNoduri + 1)
tata = [0] * (nrNoduri + 1)
dist = [None] * (nrNoduri + 1)
parcurg = []
def BFS(start):
    global lista, tata, vizitat, dist, parcurg
    q = []
    q.append(start)
    vizitat[start] = 1
    dist[start] = 0
    while len(q) > 0:
        x = q.pop(0)
        parcurg.append(x);
        for j in lista[x]:
            if vizitat[j] == 0:
                q.append(j)
                vizitat[j] = 1
                tata[j] = x
                dist[j] = dist[x] + 1

def afisare_listant(start):
    while start!=0:
        print(start, end = " ")
        start = tata[start]

start = 1
BFS(start)
print(vizitat)
print(tata)
print(dist)
print(parcurg)


f = open("control.in")
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

line = f.readline()
v = line.split()
puncte_control = []
for x in v:
    puncte_control.append(int(x))

line = f.readline()
start = int(line)

f.close()

vizitat = [0] * (nrNoduri + 1)
tata = [0] * (nrNoduri + 1)
dist = [None] * (nrNoduri + 1)
parcurg = []
def BFS(start):
    global lista, tata, vizitat, dist, parcurg
    q = [start]
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
        if parcurg[-1] in puncte_control:
            break

def afisare_listant(start):
    while start!=0:
        print(start, end = " ")
        start = tata[start]

def afisare_listan_rec(start):
    if start == 0:
        return
    else:
        afisare_listan_rec(tata[start])
        print(start, end = " ")


BFS(start)
print(lista)
print("parcurgere BFS: ", *parcurg)

print("cel mai apropiat punct de control: ", parcurg[-1])
print("listantul este:")
afisare_listan_rec(parcurg[-1])



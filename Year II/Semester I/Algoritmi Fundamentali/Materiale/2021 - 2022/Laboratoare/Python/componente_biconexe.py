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
culori = [0] * (nrNoduri + 1)
culori[1] = 1


def BFS(start):
    global lista, culori, vizitat
    q = []
    q.append(start)
    vizitat[start] = 1
    culori[start] = 1
    ok = True
    while len(q) > 0 and ok == True:
        x = q.pop(0)
        for j in lista[x]:
            if vizitat[j] == 0:
                q.append(j)
                vizitat[j] = 1
                if culori[x] == 1:
                    culori[j] = 2
                else:
                    culori[j] = 1
            else:
                if culori[j] == culori[x]:
                    ok = False
                    break

BFS(1)
print(culori[1:])
if 0 in culori[1:]:
    print("Nu e bipartit")
else:
    print("Graf bipartit")

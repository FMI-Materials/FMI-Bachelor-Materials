# Verificare daca un graf este biconex.

f = open("graf.in")

line = f.readline()
v = line.split()

n = int(v[0])
m = int(v[1])


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


lista = citire_matrice_liste(n, m, 0)
f.close()
vizitat = [0] * (n + 1)
culori = [0] * (n + 1)



def BFS(start):
    global lista, culori, vizitat
    coada = []
    coada.append(start)
    culori[start] = 1
    vizitat[start] = 1
    ok = True
    while len(coada) > 0 and ok == True:
        nod = coada.pop(0)
        for vecin in lista[nod]:
            if vizitat[vecin] == 0:
                coada.append(vecin)
                vizitat[vecin] = 1
                if culori[nod] == 1:
                    culori[vecin] = 2
                else:
                    culori[vecin] = 1
            else:
                if culori[vecin] == culori[nod]:
                    ok = False
                    break


BFS(1)
print(culori[1:])
if 0 in culori[1:]:
    print("Nu e bipartit")
else:
    print("Graf bipartit")
    print(f"Colorare: {culori[1:]}")
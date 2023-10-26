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
        x, y = v
        x = int(x)
        y = int(y)
        if orientat:
            l[x].append(y)
        else:
            l[x].append(y)
            l[y].append(x)
    return l


lista = citire_matrice_liste(n,m,0)
stiva = []
vizitat = [0] * (n + 1)
nivel = [0] * (n + 1)
nivel_minim = [0] * (n + 1)
nr_componente = 0
componentele = []

for i in range(n + 1):
    componentele.append([])
maxim = 0
componenta_max = []
muchii = []

def DFS(x,y):
    global vizitat, lista, nivel, nivel_minim, ok, nr_componente, stiva, componentele, maxim, componenta_max, muchii
    nivel[x] = nivel_minim[x] = nivel[y] + 1
    stiva.append(x)

    for nod in lista[x]:
        if nod == y:
            continue
        else:
            if nivel[nod] != 0:
                nivel_minim[x] = min(nivel_minim[x], nivel[nod])
                continue
            DFS(nod,x)
            nivel_minim[x] = min(nivel_minim[x], nivel_minim[nod])

            if nivel[x] <= nivel_minim[nod]:
                nr_componente = nr_componente + 1
                k = stiva.pop()
                componentele[nr_componente].append(k)
                while k != nod:
                    k = stiva.pop()
                    componentele[nr_componente].append(k)

                componentele[nr_componente].append(k)
                if maxim < len(componentele[nr_componente]):
                    maxim = len(componentele[nr_componente])
                    componenta_max = componentele[nr_componente]


for i in range(1, n + 1):
    if not nivel[i]:
        DFS(i,1)

print("nodurile din componenta maxima sunt:", *componenta_max)
print("muchiile care o formeaza sunt: ")
for i in range(len(componenta_max)-1):
    for j in range(i+1, len(componenta_max)):
        if componenta_max[i] in lista[componenta_max[j]]:
            print( componenta_max[i], componenta_max[j], sep=" ")




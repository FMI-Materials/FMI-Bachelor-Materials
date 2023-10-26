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

viz=[0]*(n+1)
niv_min=[0]*(n+1) #cat de sus putem ajunge din i mergand prin df
nivel=[0]*(n+1) #nivel[i] nivelul lui in arborele DF
puncte_critice=[]
start=1

def DF(x):
    global lista, viz, niv_min, nivel, puncte_critice, start
    viz[x] = 1
    niv_min[x] = nivel[x]
    for y in lista[x]:
        if viz[y] == 0:
            #(x,y) muchie de avansare
            nivel[y] = nivel[x] + 1
            DF(y)
            #actualizare niv_min[x]
            niv_min[x] = min(niv_min[x], niv_min[y])
            #testez daca (x,y) e muchie critica
            if niv_min[y] >= nivel[x] and x not in puncte_critice and x !=start:
                #radacina nu e punct critic deci o excludem
                puncte_critice.append(x)
        elif nivel[y]<nivel[x]-1: #(x,y) muchie de intoacere
            #actualizare niv_min[x]
            niv_min[x] = min(niv_min[x], nivel[y])


DF(start)
if len(puncte_critice)>0:
    print("punctele critice: ", *puncte_critice)
else:
    print("retea biconexa")
# Se dă un graf neorientat cu n>3 vârfuri și m muchii care nu este bitatatit.
# a) Să se determine un ciclu elementar imtata în graf (cu număr imtata de muchii). Se vor afișa
# muchiile unui astfel de ciclu. Complexitate O(n+m)
# b) Să se determine dacă în grad mai există în graf un alt ciclu în afară de cel afișat la punctul
# a) (nu neapărat imtata) și, în caz afirmativ, să se afișeze un astfel de ciclu (diferit de cel de la
# a)); altfel se va afișa un mesaj corespunzător. Complexitate O(n+m)
# Informațiile despre graf se citesc din fișierul graf.in cu structura:
# - pe prima linie sunt n și m
# - pe următoare

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

culoare = [0] * (n + 1)
tata = [0] * (n + 1)
numar_cicluri = 0
cicluri = []


def dfs_cycle(curent, anterior, culoare, tata):
    global numar_cicluri, lista

    if culoare[curent] == 2:
        return

    if culoare[curent] == 1:
        cicluri.append([])
        cur = anterior
        cicluri[numar_cicluri].append(cur)

        while cur != curent:
            cur = tata[cur]
            cicluri[numar_cicluri].append(cur)

        numar_cicluri += 1
        return

    tata[curent] = anterior
    culoare[curent] = 1

    for v in lista[curent]:
        if v != tata[curent]:
            dfs_cycle(v, curent, culoare, tata)
    culoare[curent] = 2


dfs_cycle(1, 0, culoare, tata)

ciclu1 = []
ciclu2 = []
for ciclu in cicluri:
    if len(ciclu) % 2 == 0 and len(ciclu2) == 0:
        ciclu2 = ciclu
    elif len(ciclu) % 2 == 1:
        if len(ciclu1) == 0:
            ciclu1 = ciclu
        elif len(ciclu2) == 0:
            ciclu2 = ciclu

print("a)")

if len(ciclu1) == 0:
    print("Nu avem cicluri de lungime impara.")
else:
    for i in range(0, len(ciclu1)):
        print(ciclu1[i], ciclu1[i-1])

    print("b)")

    for i in range(0, len(ciclu2)):
        print(ciclu2[i], ciclu2[i-1])
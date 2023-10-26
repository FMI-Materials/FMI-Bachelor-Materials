def citire_obiecte(nume_fisier):
    fin = open(nume_fisier)
    G = float(fin.readline())

    obiecte = []
    i = 0
    for linie in fin:
        aux = linie.split()
        obiecte.append((i, float(aux[0]), float(aux[1])))
        i = i+1
    """
    # alte variante de citire
    i = -1
    obiecte = [(i := i + 1,)+tuple(float(x) for x in linie.split())  for linie in fin]
    #sau
    obiecte = [(i := i + 1,*(float(x) for x in linie.split())) for linie in fin]
    #sau
    obiecte =[(i:=i+1, *map(float,linie.split()))  for linie in fin]
    """


    print(obiecte)
    fin.close()

    return G, obiecte


def cheie_obiect(ob):
    return ob[2] / ob[1]


def rucsac_fractionar(G, obiecte):

    obiecte_sortate=sorted(obiecte,key=cheie_obiect, reverse=True)
    print("obiecte sortate ",obiecte_sortate)

    G_ramasa=G
    x = [0 for i in range(len(obiecte))] #vectorul cu fractiuni
    for ob in obiecte_sortate:
        if ob[1] <= G_ramasa:
            G_ramasa -= ob[1]
            x[ob[0]] = 1 #obiectul cu indice ob[0] - luat intreg
        else:
            x[ob[0]] = G_ramasa / ob[1]
            break

    return x

def afisare(x,obiecte):
    castig_total=0
    for i in range(len(x)):
        if x[i]>0:
            print(f"Obiectul {i+1} procent {x[i]*100:.2f}%")
            castig_total += x[i]*obiecte[i][2]
    print(f"castig total {castig_total}")



G,obiecte=citire_obiecte("rucsac.in")
x=rucsac_fractionar(G,obiecte)
print("vector fractiuni x=",x)
afisare(x,obiecte)



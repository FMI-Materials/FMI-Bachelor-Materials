def cmpObiecte(obiect):
    return obiect[3]


def alegere_pivot(l):

    if len(l) <= 5:
        return sorted(l, key=cmpObiecte)[len(l)//2]

    subliste = [sorted(l[i:i + 5], key=cmpObiecte) for i in range(0, len(l), 5)]

    mediane = [sl[len(sl)//2] for sl in subliste]

    return alegere_pivot(mediane)


def linearFractionalKnapsack(obiecte, G, solutie):

    pivot = alegere_pivot(obiecte)

    # print(pivot)

    L = [el for el in obiecte if el[3] < pivot[3]]
    E = [el for el in obiecte if el[3] == pivot[3]]
    H = [el for el in obiecte if el[3] > pivot[3]]

    if sum([ob[1] for ob in H]) > G:
        linearFractionalKnapsack(H, G, solutie)
    else:
        solutie += [(*ob, 1) for ob in H]
        G -= sum([ob[1] for ob in H])
        i = 0
        while G > 0 and i < len(E):
            if E[i][1] <= G:
                solutie += [(*E[i], 1)]
                G -= E[i][1]
                i += 1
            else:
                solutie += [(*E[i], G / E[i][1])]
                G = 0

        if G > 0:
            linearFractionalKnapsack(L, G, solutie)


def scrieSolutie(numeFisier, solutie):

    fout = open(numeFisier, "w")

    for ob in solutie:
        fout.write(str(ob[0]).rjust(2) + " " + str(ob[1]).rjust(5) + " " +
                   str(ob[2]).rjust(5) + " " + str(ob[3]).rjust(5) + " " + str(ob[4]).rjust(5) + "\n")

    castigTotal = sum([ob[2] * ob[4] for ob in solutie])

    fout.write('\nCastig maxim: ' + str(castigTotal))

    fout.close()


fin = open("01.in", "r")

G = float(fin.readline())

# obiect = (ID, greutate, castig, castig unitar, fractiunea incarcata - se va adauga ulterior)
obiecte = []
for linie in fin:
    aux = linie.split()
    t = tuple((len(obiecte)+1, float(aux[0]), float(aux[1]), float(aux[1])/float(aux[0])))
    obiecte.append(t)

fin.close()

sol = []
linearFractionalKnapsack(obiecte[:], G, sol)
scrieSolutie("01.out", sol)
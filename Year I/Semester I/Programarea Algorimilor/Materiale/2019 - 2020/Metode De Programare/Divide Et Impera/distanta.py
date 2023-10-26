# Problema gasirii disntantei minime dintre niste puncte
# Divide et impera

from math import sqrt

#distanta dintre 2 puncte
def dist(p1, p2):
    return sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)


def closestPair(X, Y):
    YS, YD = [], []
    if len(X) == 2:
        return dist(*[x for x in X])
    if len(X) == 3:
        return min(dist(X[0], X[1]), dist(X[1], X[2]),dist(X[2], X[0]))

    e = X[len(X) // 2]  # aleg un element pivot, asta imi imparte punctele in doua zone

    XS = [x for x in X[    :len(X) // 2 + 1]]  # astea sunt la stanga pe pivot
    XD = [x for x in X[len(X) // 2 + 1:    ]]  # astea la dreapta

    for x in Y:  # pt fiecare punct din cele sortate pe veritcala
        if x[0] <= e[0]:  # daca sunt la stanga pivotului
            YS.append(x)  # le adaug la cele din stanga
        else:
            YD.append(x)  # altfel le adaug la cele din dreapta
        d1 = closestPair(XS, YS)  # gasesc cea mai mica dist in stanga
        d2 = closestPair(XD, YD)  # gasesc cea mai mica dist in dreapta
        d = min(d1, d2)  # gasesc cea mai mica dist dintre cele doua zone

    # acum trebuie sa gasesc daca nu cumva exista o distanta mai mica in vecinanatea pivotului
    # (e[0]-d,e[0]+d)e[0]-coord x a pivotului
    SS = [x for x in XS if (x[0] > e[0] + d)]  # cele pe banda (e[0]-d)
    SD = [x for x in XD if (x[0] < e[0] + d)]  # cele pe banda (e[0]+d)
    S = SS + SD  # toata banda
    S.sort(key=lambda x: x[1])
    # a ramas doar sa caut in banda aia specifica o distanta mai mica decat d
    for x in S:
        for y in S:
            if dist(x, y) != 0 and dist(x, y) < d:
                d = dist(x, y)



    return d


P = [(0, 0), (1, 3), (3, 2), (1, 5), (5, 5)]
X = sorted(P, key=lambda x: x[0])
print(X)
Y = sorted(P, key=lambda x: x[1])  # punctele sortate dupa x , respectiv y
print(Y)
print(closestPair(X, Y))
def citire():
    n = int(input())
    v = [int(x) for x in input().split()]
    return n, v


def afisare(v):
    print(v, sep=" ")


def valpoz(v):
    poz = []
    for i in v:
        if i > 0:
            poz.append(i)
    return poz


def semn(v):
    for i in range(len(v)):
        v[i] = -v[i]

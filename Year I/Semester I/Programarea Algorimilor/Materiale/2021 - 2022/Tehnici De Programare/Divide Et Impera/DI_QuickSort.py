from random import randint


def citire_vector(nume_fisier):
    f = open(nume_fisier)
    ls = [int(x) for x in f.read().split()]

    return ls


def poz_rand(v, p, u):
    r = randint(p, u)
    v[r], v[p] = v[p], v[r]
    return poz(v, p, u)


def poz(v, p, u):
    i = p
    j = u
    depli = 0
    deplj = -1
    while i < j:
        if v[i] > v[j]:
            v[i], v[j] = v[j], v[i]
            depli, deplj = -deplj, -depli
            #aux = depli;  depli = -deplj; deplj = -aux
        i += depli
        j += deplj

    return i


def quick_sort_di(v, p, u):

    if p >= u:
        return
    m = poz_rand(v, p, u)
    #m = poz(v, p, u)
    quick_sort_di(v, p, m - 1)
    quick_sort_di(v, m + 1, u)



def quick_sort(v):
    return quick_sort_di(v, 0, len(v) - 1)


v = citire_vector("interclasare.in")
quick_sort(v)
print(v)

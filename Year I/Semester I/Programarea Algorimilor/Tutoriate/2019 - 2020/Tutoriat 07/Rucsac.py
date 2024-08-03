import random

with open("rucsac.in", "r") as r:
    weight = int(r.readline())
    obji = [[float(y) for y in x.split()] for x in r.read().split('\n')]
    obji = [[x[1], x[0], round(x[1]/x[0], 2)] for x in obji]

def bfprt(a):
    if len(a) <= 5:
        a = sorted(a, key=lambda x: x[2], reverse=1)
        return a[len(a)//2]
    sub = [sorted(a[x:x+5], key=lambda x: x[2], reverse=1) for x in range(0, len(a), 5)]
    med = [x[len(x)//2] for x in sub]
    return bfprt(med)


def calc(a):
    p = 0
    for x in a:
        p += x[0]
    return p


def partition(l, r, a):
    piv_p = r #obji.index(bfprt(a[:]))
    piv = a[piv_p][2]
    i = l
    g = a[r][1]
    for j in range(l, r):
        if a[j][2] >= piv:
            g += a[j][1]
            a[j], a[i] = a[i], a[j]
            i += 1
    a[piv_p], a[i] = a[i], a[piv_p]
    return [i, g]


def rucsac(l, last_w, r, a, weight):
    if l > r:
        diff = weight-last_w
        diff_p = diff/a[l][1]
        add = diff_p * a[l][0]
        return calc(a[:l]) + round(add, 2)
    res = partition(l, r, a)
    m = res[0]
    g = res[1]
    if g + last_w == weight:
        return calc(a[:m])
    elif g + last_w < weight:
        return rucsac(m+1, g+last_w, r, a[:], weight)
    else:
        return rucsac(l, last_w, m-1, a[:], weight)


random.shuffle(obji)

print(rucsac(0, 0, len(obji)-1, obji[:], weight))



from random import randint


def mediana_sortare(): #nlog(n)
    l_s.sort()

    s=0
    i=0
    while(s<0.5):
        s=s+l_s[i][1]
        i+=1

    i-=1
    return l_s[i][0]


def poz_rand(v, w,p, u):
    r = randint(p, u)
    v[r], v[p] = v[p], v[r]
    w[r], w[p] = w[p], w[r]
    return poz(v, w,p, u)


def poz(v, w, p, u):
    i = p
    j = u
    depli = 0
    deplj = -1
    while i < j:

        if v[i] > v[j]:
            v[i], v[j] = v[j], v[i]
            w[i], w[j] = w[j], w[i]
            depli, deplj = -deplj, -depli
            #aux = depli;  depli = -deplj; deplj = -aux
        i += depli
        j += deplj

    return i


def mediana(x,w, p, u):

    if  (p==u):
        return x[p]

    m = poz_rand(x,w, p, u)

    s1 = sum(w[p:m]) #suma stanga
    s2 = sum(w[m+1:u+1]) #suma dreapta

    if (s1 < 0.5) and (s2 <= 0.5):
        return x[m]
    if s1>=0.5: #adaug ponderea din dreapta la pivot si merg in stanga
        w[m]=w[m]+s2
        return mediana(x,w, p, m)
    else:#adaug ponderea din stanga la pivot si merg in dreapta
        w[m] = w[m] + s1
        return mediana(x, w, m, u)
x=[4,1,3,2,6,7,5]
w=[0.1,0.12,0.05,0.1,0.2,0.3,0.13]
#x=[4,1]
#w=[0.9,0.1]
l_s=[]
for i in range(len(x)):
    l_s.append((x[i],w[i],i))
print(mediana_sortare()) #- de verificare
print(mediana(x,w,0,len(x)-1))
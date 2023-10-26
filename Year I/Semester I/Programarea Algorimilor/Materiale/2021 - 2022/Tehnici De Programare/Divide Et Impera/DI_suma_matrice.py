def citire_matrice(nume_fisier):
    f=open(nume_fisier)
    m=[]
    for linie in f:
        m.append([int(x) for x in linie.split()])
    f.close()
    return m

def suma(m,x,y,n):
    print(x,y)
    if n==1:
        return m[x][y] #!!da eroare cu n/2, e de tip float

    s1 = suma(m, x, y, n//2)
    s2 = suma(m, x+n//2, y, n//2)
    s3 = suma(m, x, y+n//2, n//2)
    s4 = suma(m, x+n//2, y+n//2, n//2)
    return s1+s2+s3+s4

def suma_matrice(m):
    return suma(m,0,0,len(m))
m=citire_matrice("matrice.in")
s=0
for linie in m:
    s=s+sum(linie)
print(s)
print(suma_matrice(m))

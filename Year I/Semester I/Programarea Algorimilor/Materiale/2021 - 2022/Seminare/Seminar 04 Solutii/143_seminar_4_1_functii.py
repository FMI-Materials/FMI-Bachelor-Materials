def suma(n, f=int): #param cu val default - nu este obligatoriu sa primeasca valaore la apel
    s=0
    for i in range(1,n+1):
        s+=f(i)
    return s

print(suma(10))
import math
print(suma(10,math.sqrt)) #se pot trimite param si prin pozitie si prin nume
def radical(x):
    return x**0.5
print(suma(10,f=radical))

#b)
def suma_b(*numere, f=int): #param cu val default - nu este obligatoriu sa primeasca valaore la apel
    s=0
    for i in numere:
        s+=f(i)
    return s

print(suma_b(2,3,4,5))
ls = [3,1,7]
print(suma_b(*ls))
#print(suma(ls))
from math import sqrt
print(suma_b(4,9,16,f=sqrt)) #f obligatoriu sa fie apelat cu nume


f=open("numere.txt")
#citim tot fisierul cu f.read() - si il imaprtim cu split() - dupa caracterele albe
ls = [int(x) for x in f.read().split()]
print(ls)
f.close()


f=open("numere.txt")
#citim linie cu linie
ls = []
for linie in f:
    #ls.append([int(x) for x in linie.split()]) #matrice
    ls.extend([int(x) for x in linie.split()])
print(ls)
f.close()

print(suma_b(*ls, f=sqrt))
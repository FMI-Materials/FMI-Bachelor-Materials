""" 12. a) Scrieti o functie genericã de cãutare având urmãtorul antet: 
cautare(x, L, cmpValori)
Functia trebuie sã returneze indexul ultimei aparitii a valorii x în lista L 
sau None dacã valoarea x nu se gãseste în listã. 
Functia comparator cmpValori se considerã cã returneazã True dacã valorile 
primite ca parametri sunt egale sau False în caz contrar.

b) Scrieti o functie care sã afiseze, folosind apeluri utile ale functiei cautare, 
mesajul DA în cazul în care o listã L formatã din n numere întregi este palindrom 
sau mesajul NU în caz contrar. 
O listã este palindrom dacã prin parcurgerea sa de la dreapta la stânga 
se obtine aceeasi listã.
De exemplu, lista L=[101,17,101,13,5,13,101,17,101] este palindrom.
"""

def cmpValori(x, y):
    return x == y

def cautare(x, L, cmpValori):
    for i in range(len(L)-1, -1, -1):
        if cmpValori(x, L[i]):
            return i
    return None

def palindrom(L):
    n = len(L)
    for i in range(n//2):
        if cautare(L[i], L[:n-i], cmpValori) != n-i-1:
            return False
    return True


L = [101, 17, 101, 13, 5, 13, 101, 17, 101]
print(palindrom(L))


# Varianta "pythonica" :)))
print(L == L[::-1])
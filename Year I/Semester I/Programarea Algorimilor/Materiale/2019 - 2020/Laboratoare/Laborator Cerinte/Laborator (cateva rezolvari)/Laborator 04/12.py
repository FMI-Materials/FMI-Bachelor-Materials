""" 12. a) Scrieti o functie generic� de c�utare av�nd urm�torul antet: 
cautare(x, L, cmpValori)
Functia trebuie s� returneze indexul ultimei aparitii a valorii x �n lista L 
sau None dac� valoarea x nu se g�seste �n list�. 
Functia comparator cmpValori se consider� c� returneaz� True dac� valorile 
primite ca parametri sunt egale sau False �n caz contrar.

b) Scrieti o functie care s� afiseze, folosind apeluri utile ale functiei cautare, 
mesajul DA �n cazul �n care o list� L format� din n numere �ntregi este palindrom 
sau mesajul NU �n caz contrar. 
O list� este palindrom dac� prin parcurgerea sa de la dreapta la st�nga 
se obtine aceeasi list�.
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
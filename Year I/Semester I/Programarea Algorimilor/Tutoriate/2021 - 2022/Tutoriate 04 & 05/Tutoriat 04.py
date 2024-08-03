# TUTORIAT 4 (SORTARI + TUPLURI)
# ex5 (Tutoriat 3)
# m = int(input("m="))
# n = int(input("n="))
# x = int(input("x="))
# matrice = [[0 for j in range(n)] for i in range(m)]
# for i in range(m):
#     for j in range(n):
#         print(matrice[i][j], end=" ")
#     print()
# a)
#
# b)
# suma_maxima = -1
# indice = -1
# for j in range(n):
#     suma = 0
#     for i in range(m):
#         suma += matrice[i][j]
#     if suma > suma_maxima:
#         suma_maxima = suma
#         indice = j
# print(suma_maxima, j)

# c)
# diagonala principala => i = j
# diagonala secundara => i + j = n - 1 => i = n - j - 1
# deasupra diagonalei principale => i < j
# sub diagonala principala => i > j
# deasupra diagonalei secundare => i + j < n - 1
# sub diagonala secundara => i + j > n - 1
#
# suma = 0
# for i in range(m):
#     suma += matrice[i][i]
# print(f"Suma elementelor de pe diagonala principala: {suma}")
#
# produs = 1
# for j in range(n):
#     produs *= matrice[n-j-1][j]
# print(f"Produsul elementelor de pe diagonala secundara: {produs}")
#
# suma_impare = 0
# for i in range(m):
#     for j in range(n):
#         if i > j and i + j < n - 1 and matrice[i][j] % 2 == 1:
#             suma_impare += matrice[i][j]
# print(f"Suma elementelor din zona data: {suma_impare}")

# citire elemente matrice, fiecare linie pe un rand
# 0 5 10 15
# m = int(input("m="))
# matrice1 = []
# for i in range(m):
#     linie = [int(x) for x in input().split()]
#     matrice1.append(linie)
#
# for i in range(m):
#     for elem in matrice1[i]:
#         print(elem, end=" ")
#     print()

# citire matrice cu m linii, n coloane, element cu element
# m = int(input("m="))
# n = int(input("n="))
# matrice2 = []
# for i in range(m):
#     linie = []
#     for j in range(n):
#         linie.append(int(input("elem=")))
#     matrice2.append(linie)
#
# for i in range(m):
#     for elem in matrice2[i]:
#         print(elem, end=" ")
#     print()

# ex1
import functools


def numar_cifre(a):
    cifre = 0
    while a:
        cifre += 1
        a //= 10
    return cifre


def comparare(a, b):
    if numar_cifre(a) < numar_cifre(b):
        return -1
    if numar_cifre(a) == numar_cifre(b):
        return 0
    if numar_cifre(a) > numar_cifre(b):
        return 1


n = int(input("n="))
lista = []
for i in range(n):
    lista.append(int(input("elem=")))
lista.sort(key=functools.cmp_to_key(comparare))
print(lista)

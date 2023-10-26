# TUTORIAT3 (LISTE)

# exp1 (moduri de creare liste)
# nume_lista = list()
# nume_lista = [1, 14, -5, 7, 100]
# print(nume_lista)
# new_list = list("tutoriat")
# print(new_list)

# comprehensiune
# lista1 = [a**2 for a in range(2, 5)]
# print(lista1)
# lista2 = [a for a in range(1, 20) if a % 2 == 0]
# print(lista2)
# lista3 = [a if a > 0 else -a for a in range(-5, 4)]
# print(lista3)

# exemple accesare elemente
# my_list = [4, 12, [2, 6], -4, [1, 8, 16]]
# print(my_list)
# print(my_list[1])
# print(my_list[4])
# print(my_list[2][1])
# print(my_list[4][0])
# print(my_list[4][2])
# print(my_list[-1])

# exemple copiere
# lista2 = [1, 2, 3, 4]
# print(lista2, id(lista2))
# lista_noua = lista2.copy()
# print(lista_noua, id(lista_noua))
# lista3 = lista2
# lista2[2] = 5
# print(lista2)
# print(lista_noua)
# print(lista3)

# copiere superficiala pentru lista cu elemnte colectii
# l1 = [[1, 5], [2, 3], [1, 2]]
# l2 = l1.copy()
# l2[0][0] = 10
# print(l1)
# print(l2)

# accesare elemente
# nume_lista = [a**2 for a in range(2, 5)]
# print(nume_lista)
# print(nume_lista[1])
# print(nume_lista[2:4])
# print(nume_lista[:5])
# print(nume_lista[3:])
# print(nume_lista[:])
# print(nume_lista[1:6:2])

# operatori ==, >, <, != pe liste
# lista1 = [1, 5, 9, 13]
# lista2 = [2, 3, 11]
# print(lista1)
# print(lista2)
# print(lista1 == lista2)
# print(lista2 > lista1)
# print(lista1 < lista2)
# print(lista1 != lista2)

# stergere elemente lista
# lista1 = [2, 5, 8, 10, 4]
# print(lista1)
# lista1.clear()
# print(lista1)

# modificare elemente lista
# lis = [1, 5, -2, 0, 4]
# lis[2] = 10
# print(lis)
# lis[1:3] = [2,5]
# print(lis)
# lis[1:5:2] = [1, 6]
# print(lis)
# del lis[2:5]
# print(lis)

# EXERCITII

# ex1
#  citire lista cu n elemente
# n = int(input("n="))
# lista = []
# for i in range(n):
#     lista.append(int(input("elem=")))
# print(lista)
#
# y = int(input("y = "))
# ls = [x for x in lista if x != y]
# print(ls)

# ex2
# l_original = [1, 2, [3, [4, 5, [6, 7], 11], 12], 13, 14]
# l_add = [8, 9, 10]
# l_original[2][1][2].extend(l_add)
# print(l_original)

# ex3
# a) lista numerelor pare din intervalul [2, 25]
# varianta 1
# lista_pare = [x for x in range(2, 25) if x % 2 == 0]
# print(lista_pare)
# varianta 2
# lista_pare2 = [x for x in range(2, 25, 2)]
# print(lista_pare2)

# b)lista cu elementele de forma -1, 2, -3, 4, -5,.., +/- n, n citit de la tastatură
# n = int(input("n="))
# lista2 = [x if x % 2 == 0 else -x for x in range(1, n+1)]
# print(lista2)

# c) lista cu elementele de pe poziții pare ale unei liste list1 citită de la tastatură
# n = int(input("n="))
# lista = []
# for i in range(n):
#     lista.append(int(input("elem=")))
# print(lista)
# lista3 = [lista[x] for x in range(0, n, 2)]
# print(lista3)

# d)lista elementelor, dintr-o listă dată, care au paritate diferită de poziția lor
# lista = [2, 4, 5, 8, 10, 15]
# lista_rez = [lista[x] for x in range(len(lista)) if x % 2 != lista[x] % 2]
# print(lista_rez)

# e)
# n = int(input("n="))
# ls = [[] if l == 0 else [l] * l for l in range(n)]
# print(ls)

# ex4
# n = int(input("n="))
# my_list = []
# # retinem paritatea sumei cifrelor, astfel:
# # paritate[i]=0 daca suma cifrelor lui i este para
# # paritate[i]=1 daca suma cifrelor lui i este impara
# paritate = []
# for i in range(n):
#     my_list.append(int(input("elem=")))
# # calculam suma cifrelor fiecarui element din lista
#     aux = my_list[i]
#     suma_cifre = 0
#     while aux:
#         suma_cifre += aux % 10
#         aux //= 10
#     if suma_cifre % 2 == 0:
#         paritate.append(0)
#     else:
#         paritate.append(1)

# print(paritate)

# ordonam elementele astfel:
# suma cifrelor para -> descrescator
# suma cifrelor impara -> crescator
# for i in range(len(my_list)-1):
#     for j in range(i+1, len(my_list)):
#         if (paritate[i] == 0 and paritate[j] == 0 and my_list[i] < my_list[j]
#         or paritate[i] == 1 and paritate[j] == 1 and my_list[i] > my_list[j]
#         or paritate[i] == 1 and paritate[j] == 0):
#             aux = my_list[i]
#             my_list[i] = my_list[j]
#             my_list[j] = aux
#             aux = paritate[i]
#             paritate[i] = paritate[j]
#             paritate[j] = aux
#
# print(my_list)

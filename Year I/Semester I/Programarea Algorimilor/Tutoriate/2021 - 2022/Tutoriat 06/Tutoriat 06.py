# # TUTORIAT 6
# # exemple
# dict1 = {"b": 2, "c": 3, "d": 4}
# dict1.update({"f": 4, "d": 5})
# print(dict1)
# dict1.pop("D")
# val = dict1.pop("D", 0)
# print(val)
# del dict1["d"]
# print(dict1)
# for cheie in dict1.keys():
#     print(cheie)
# print(dict1.values(), type(dict1.values()))
# print(dict1.items())
#
# my_set = set("tutoriat")
# print(my_set)

# #ex1
# n = int(input("n="))
# lista1 = list()
# lista2 = []
# for i in range(n):
#     lista1.append(input("elem1= "))
# for i in range(n):
#     lista2.append(input("elem2= "))
# res_dict = dict()
# # metoda 1
# for i in range(n):
#     res_dict[lista1[i]] = lista2[i]
# print(res_dict)

# # metoda 2
# for i in range(n):
#     res_dict.update({lista1[i]: lista2[i]})
# print(res_dict)

# # metoda 3
# print(zip(lista1, lista2))
# res_dict = dict(zip(lista1, lista2))
# print(res_dict)

# # ex2
# dict1 = { "nume": "Ana", "varsta": 30, "salariu":10000, "oras": "Cluj" , "ore": 45}
# lista = ["nume", "salariu", "ore"]
# new_dict = {}
# # metoda 1
# for cheie in lista:
#     new_dict.update({cheie: dict1[cheie]})
# print(new_dict)
# # metoda 2
# new_dict2 = {cheie: dict1[cheie] for cheie in lista}
# print(new_dict2)

# ex3
# a)
n = int(input("n="))
my_list = []
for i in range(n):
    student = (input().split(" ", 1))
    my_list.append((int(student[0]), student[1], i + 1))
print(my_list)

# b)
punctaje = {i[0] for i in my_list}
print(punctaje)

# c)
my_dict = {}
for punctaj in punctaje:
    my_dict[punctaj] = [x[1:] for x in my_list if x[0] == punctaj]
print(my_dict)

# d)
punctaj_maxim = my_dict[max(my_dict)][0]
print(punctaj_maxim)

# # ex1(multimi)
# n = int(input("n="))
# m = int(input("m="))
# set1 = set()
# set2 = set()
# for i in range(n):
#     set1.add(int(input("elem1=")))
# for i in range(m):
#     set2.add(int(input("elem1=")))
# print(set1)
# print(set2)
# set3 = set1.symmetric_difference(set2)
# print(set3)

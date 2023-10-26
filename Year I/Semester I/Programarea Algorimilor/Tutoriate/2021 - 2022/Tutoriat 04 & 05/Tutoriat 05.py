# TUTORIAT 5 (continuare exercitii tutoriat 4)

# ex.2
# import functools
#
#
# def numar_cifre_pare(a):
#     nr_cifre = 0
#     while a:
#         if (a % 10) % 2 == 0:
#             nr_cifre += 1
#         a //= 10
#     return nr_cifre
#
#
# def comparare(a, b):
#    if numar_cifre_pare(a) < numar_cifre_pare(b):
#        return -1
#    if numar_cifre_pare(a) == numar_cifre_pare(b):
#        return 0
#    if numar_cifre_pare(a) > numar_cifre_pare(b):
#        return 1
#
#
# n = int(input("n="))
# my_list = []
# for i in range(n):
#     my_list.append(int(input("elem=")))
# my_list.sort(key=functools.cmp_to_key(comparare), reverse=True)
# print(my_list)

# ex.3
# n = int(input("n="))
# my_list = []
# for i in range(n):
#     my_list.append(int(input("elem=")))
# my_list.sort(key=lambda a: a % 10)
# print(my_list)

# tuplu1 = 2, 5, 10, 14
# print(tuplu1, type(tuplu1))
# print(tuplu1[3])
# print(tuplu1[0:2])
# print(tuplu1[:])
# tuplu2 = (10)
# tuplu2 = (10, )
# print(tuplu2, type(tuplu2))

# my_list = [i ** 2 for i in range(6)]
# my_list[2] = 7
# print(my_list, type(my_list))
# my_tuple = (i ** 2 for i in range(6))
# print(my_tuple, type(my_tuple))
#
# my_tuple = ([2, 5, 8], [10, 5], 4, "afara")
# my_tuple[0][2] = 7
# my_tuple[1].extend(range(2))
# my_tuple[0].append(12)
# print(my_tuple)
# my_tuple[3] = "Ana"
# my_tuple[2] = 5

# a, b = (10, 20)
# print(a, b)

# def functie_multipla():
#     x = 14
#     y = "afara"
#     return x, y
#
# var = functie_multipla()
# print(var, type(var))

# c, d, *e = 4, 10, 25, 45, 8
# print(c, d, e)

# a = 10
# b = 30
# a, b = b, a
# print(a, b)

# ex.4
# 123 Informatica 5
# a)
# n = int(input("n="))
# my_list = []
# for i in range(n):
#     my_list.append(tuple(input().split()))
# print(my_list)

# # b)
# import functools


# def comparare(a, b):
#     if a[0] < b[0]:
#         return -1
#     if a[0] > b[0]:
#         return 1
#     if a[0] == b[0]:
#         if a[1] < b[1]:
#             return -1
#         if a[1] == b[1]:
#             return 0
#         if a[1] > b[1]:
#             return 1


# l_rez = sorted(my_list, key=functools.cmp_to_key(comparare))
# print(l_rez)

# # c)


# def comparare2(a, b):
#     if a[2] < b[2]:
#         return -1
#     if a[2] > b[2]:
#         return 1
#     if a[2] == b[2]:
#         if a[1] < b[1]:
#             return -1
#         if [a1] == b[1]:
#             return 0
#         if a[1] > b[1]:
#             return 1


# for i in range(n):
#     print(my_list[i])
# l_rez2 = sorted(my_list, key=functools.cmp_to_key(comparare2), reverse=True)
# print(l_rez2)

# # ex5
# tuplu1 = (10, 20, 30)
# tuplu2 = (40, 50, 60)
# tuplu1, tuplu2 = tuplu2, tuplu1
# print(tuplu1, tuplu2)

# ex6
tuple1 = (("a", 10), ("z", 14), ("c", 20))
sorted_tuple_1 = sorted(tuple1, key=lambda x: x[0])
print(sorted_tuple_1)
sorted_tuple_2 = sorted(tuple1, key=lambda x: x[1])
print(sorted_tuple_2)

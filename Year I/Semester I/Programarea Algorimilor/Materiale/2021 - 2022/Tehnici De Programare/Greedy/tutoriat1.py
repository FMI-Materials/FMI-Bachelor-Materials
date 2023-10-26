# TUTORIAT1
# exemple
# a = 5
# print(type(a))
# a = 2.5
# print(type(a))
# a = 2+6j
# print(type(a))
# print("Ana are mere", 2, sep="*", end=" ")
# print(2 + 3)
# a = float(input("a="))
# print(type(a))

# ex1
# a = int(input("a="))
# b = int(input("b="))
# c = int(input("c="))
# if a+b > c and a+c > b and b+c > a:
#     print("Este triunghi")
# else:
#     print("Nu este triunghi")


# ex2
# n = int(input("n="))
# i = 1
# while i * i * i < n:
#     i = i + 1  # i += 1
# if i * i * i == n:
#     print("Este cub")
# else:
#     print("Nu este cub")

# ex3
# n = int(input("n="))
# if n % 2 == 1:
#     print("Weird")
# elif n % 2 == 0 and 2 <= n <= 5:
#     print("Not Weird")
# elif n % 2 == 0 and 6 <= n <= 20:
#     print("Weird")
# elif n % 2 == 0 and n > 20:
#     print("Not Weird")

# ex4
# a = int(input("a="))
# b = int(input("b="))
# for i in range (a, b+1):
#     for divizor in range(2, i//2+1):
#         if i % divizor == 0:
#             break
#     else:
#         print(i)
#         break
# else:
#     print("Nu exista numar prim in intervalul dat")

# ex5
# a = int(input("a="))
# b = int(input("b="))
# maxim_divizori_primi = -1
# for i in range(a, b+1):
#     numar_divizori = 0
#     divizor = 2
#     temp = i
#     while temp > 1:
#         if temp % divizor == 0:
#             numar_divizori += 1
#             while temp % divizor == 0:
#                 temp /= divizor
#         else:
#             divizor += 1
#     if numar_divizori > maxim_divizori_primi:
#         maxim_divizori_primi = numar_divizori
#
# for i in range (a, b+1):
#     numar_divizori = 0
#     divizor = 2
#     temp = i
#     while temp > 1:
#         if temp % divizor == 0:
#             numar_divizori += 1
#             while temp % divizor == 0:
#                 temp /= divizor
#         else:
#             divizor += 1
#     if numar_divizori == maxim_divizori_primi:
#         print(i, end=" ")

# ex6
# n = int(input("n="))
# min1 = int(input("min1="))
# min2 = int(input("min2="))
# min1, min2 = min(min1, min2), max(min1, min2)
# for i in range(n-2):
#     nr = int(input("nr="))
#     if nr < min1:
#         min2 = min1
#         min1 = nr
#     elif nr < min2:
#         min2 = nr
# if min1 != min2:
#     print(min1, min2)
#
# else:
#     print("Nu se poate")

# ex7
# varianta1
# import math
# print(math.sqrt(4))

# varianta2
from math import sqrt
print(sqrt(4))

x = int(input("x="))
val_fct = int()
if x < -9:
    val_fct = abs(x)
elif -9 < x < 0:
    val_fct = sqrt(x+9)
elif 0 <= x < 10:
    val_fct = x ** 2
print("Valoarea functiei f(x) este:", end="")
print(val_fct)


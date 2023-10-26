# Tutoriat 2 (SIRURI DE CARACTERE)

# exemple creare sir de caractere
# first_string = 'Welcome Tutoriat2 '
# second_string = "It`s time to study ."
# third_string = ' ' ' It`s time to have fun ! ' ' '
# another_string = str(1.44)

# test apartenenta
# nume_sir = "Este luni, ne aflam la tutoriat."
# if 'z' not in nume_sir:
#    print("z nu se gaseste in sir")
# if "ne" in nume_sir:
#    print("Secventa ne se gaseste in sir")

# concatenare
# s1 = "Facultatea de Matematica "
# s2 = "si Informatica"
# s1 = s1 + s2

# formatare siruri
# sir = "Numele meu este {} si am {} ani".format("Andrei", 12)
# #print(sir)
# nume = "Andrei"
# varsta = 12
# sir = "Numele meu este {} si am {} ani".format(nume, varsta)
# print(sir)
# sir = "Numele meu este {1} si am {0} ani".format(nume, varsta)
# print(sir)

# suma = 6.4 + 5.9
# print('{:f}'.format(suma))
# print('{:.2f}'.format(suma))
# print('{:.8f}'.format(suma))

# ex1
# s1 = input("s1=")
# s2 = input("s2=")
# s3 = ""
# s2 = s2[::-1]
# s1_length = len(s1)
# s2_length = len(s2)
# length = max(s1_length, s2_length)
#
# for i in range(length):
#     if i < s1_length:
#         s3 = s3 + s1[i]
#     if i < s2_length:
#         s3 = s3 + s2[i]
# print(s3)

# ex2
# s1 = input("s1=")
# s2 = input("s2=")
#
# temp_s1 = s1.lower()
# count_ap = s1.lower().count(s2.lower())
# print("Sirul s2 se gaseste in s1 de {} ori".format(count_ap))

# ex 3
# suma = 0
# produs = 1
# cnt = 0
# sir = input("sir=")
# for char in sir:
#     if char.isdigit():
#         suma += int(char)
#         produs *= int(char)
#         cnt += 1
# print("Suma {}, produsul {}".format(suma, produs))
# if cnt > 0:
#     print("Media", suma/cnt)

# import string
# ex4
# sir = "/*Is it an #$% important @ day ?!"
# print(sir)
# sir_aux = string.punctuation
# print(sir_aux)
# for char in sir_aux:
#     sir = sir.replace(char, '*')
# print(sir)

# ex5
# sir = input("sir=")
# s = input("s=")
# midle_index = int(len(sir)/2)
# sir = sir[:midle_index:] + s + sir[midle_index:]
# print(sir)

# ex6
# s = "Programarea este o Disciplina de Viitor"
# sir = ""
# for i in range(len(s)):
#     if s[i].isalpha() and s[i].isupper():
#         sir = sir + s[i].lower()
#     else:
#         sir = sir + s[i]
# print(sir)

# ex7
# s = "abcdef"
# rezultat = ""
# for i in range(len(s)):
#     if i % 2 == 0:
#         rezultat += s[i]
# print(rezultat)

# ex8
# x = 3.1415926
# y = 12.9999
# print(x)
# print("{:.2f}".format(x))
# print(y)
# print("{:.2f}".format(y))

# ex10
# s1 = input("s1=")
# s2 = input("s2=")
# rezultat = str()
#
# if s1[-1] == s2[0]:
#     rezultat = s1[0:len(s1)-1] + s2
# elif s1[1] == s2[-2]:
#     rezultat = s1 + s2
# print(rezultat)

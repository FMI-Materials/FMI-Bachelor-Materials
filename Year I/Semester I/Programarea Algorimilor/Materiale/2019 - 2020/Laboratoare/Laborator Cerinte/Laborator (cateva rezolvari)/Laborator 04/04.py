""" 4. (Generator)
Implementati un generator infinit de numere prime. 
Folosind acest generator, scrieti un program care citeste de la tastaturã 
un numãr natural nenul n>=2 si afiseazã pe ecran:
a) numerele prime cel mult egale cu n;
b) primele n numere prime.
"""

# def nr_prime():
#     def e_prim_impar(x):
#         for d in range(3, x//2 + 1, 2):
#             if x % d == 0:
#                 return False
#         return True
#
#     yield 2
#     x = 3
#     while True:
#         if e_prim_impar(x):
#             yield x
#         x += 2

def nr_prime():
    yield 2
    x = 3
    while True:
        for d in range(3, x//2 + 1, 2):
            if x % d == 0:
                break
        else:
            yield x
        x += 2

while True:
    n = int(input("Introduceti un nr nat nenul >=2 : "))
    if n >= 2:
        break

print(f"\na) Numerele prime <= {n} sunt:")
for p in nr_prime():
    if p > n:
        break
    print(p, end=" ")

print(f"\n\nb) Primele {n} numere prime sunt:")
i = n
gen = nr_prime()
while i != 0:
    print(next(gen), end=" ")
    i -= 1
a = int(input("a = "))
b = int(input("b = "))
z = b

for i in range(5, a, 5):
    print(i, end=" ")
b = b + 1
while b % 5 != 0:
    b = b + 1
for i in range(b, 100, 5):
    print(i, end=" ")

print()

b = z
for i in range(95, b, -5):
    print(i, end = " ")
a = a - 1
while a % 5 != 0:
    a = a - 1
for i in range(a, 4, -5):
    print(i, end = " ")
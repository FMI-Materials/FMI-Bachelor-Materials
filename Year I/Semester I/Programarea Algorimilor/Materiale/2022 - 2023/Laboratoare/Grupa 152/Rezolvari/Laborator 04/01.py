import math as m

cout = open("Txt Files/Triplete_pitagorice.txt", "w")


def ipotenuza(a, b):
    c = m.sqrt(a ** 2 + b ** 2)
    return c


b = int(input())
for a in range(1, b):
    c = int(ipotenuza(a, b))
    if c * c == a * a + b * b:
        cout.write(f"({a}, {b}, {c})\n")

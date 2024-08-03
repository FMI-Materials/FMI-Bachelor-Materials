""" 1. În fișierul text “date.in” sunt memorate, pe linii, numele și prenumele
studenților dintr-o grupă.
Să se scrie un program care să genereze conturile de email ale studenților și
parolele temporare, după care să le salveze în fișierul text de tip CSV “date.out”.

Contul de email al unui student va fi de forma prenume.nume@myfmi.unibuc.ro,
iar parola temporară va fi de forma o literă mare, 3 litere mici și 4 cifre."""

from string import digits, ascii_lowercase, ascii_uppercase
from random import choices

f = open("L3_pb1_date.in", "r")
L = f.readlines()
f.close()

g = open("L3_pb1_date.out", "w")
for s in L:
    [nume, prenume] = s[:-1].split(" ") # s-ul fara "\n"
    email = (prenume + "." + nume).lower() + "@myfmi.unibuc.ro"

    A = choices(ascii_uppercase)
    a = choices(ascii_lowercase, k=3)
    cif = choices(digits, k=4)
    parola = "".join(A+a+cif)

    g.write(email + "," + parola + "\n")
g.close()
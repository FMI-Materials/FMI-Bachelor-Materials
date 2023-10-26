""" 3. Scrieti un program care sa inlocuiasca intr-o propozitie
toate aparitiile unui cuvant s cu un cuvant t.
Atentie, NU se poate utiliza metoda replace! De ce?"""

# sir = "ana bana cana ana, sana ana lana."
# s = "ana"
# t = "ANA"
# => sir_1 = "ANA bana cana ANA, sana ANA lana."
sir = input("Sir: ")
s = input("cuvant vechi: s = " )
t = input("cuvant nou: t = ")

k = len(s)
p = len(t)
sir_1 = sir

poz = sir_1.find(s)
while poz != -1:
    if (poz == 0 or sir_1[poz-1].isalpha() == False) \
            and (poz+k == len(sir_1) or sir_1[poz+k].isalpha() == False):
        sir_1 = sir_1[:poz] + sir_1[poz:].replace(s,t,1)
    poz = sir_1.find(s, poz+p)

print("\nSirul dupa inlocuiri:")
print(sir_1)
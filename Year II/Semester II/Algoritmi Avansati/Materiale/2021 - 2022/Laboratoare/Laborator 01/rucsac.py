def citire(fisier):
    f = open(fisier, "r")
    
    nrSaci = int(f.readline())

    saci = []

    for i in range(nrSaci):
        v, w = [int(x) for x in f.readline().split()]

        saci.append((v/w, v, w))

    capacitate = int(f.readline())

    f.close()

    return nrSaci, saci, capacitate

nrSaci, saci, capacitate = citire("rucsac.in")

print(nrSaci, saci, capacitate)

# ordonam sacii descrescator dupa valoare
# pentru a ajunge la profitul maxim

saci.sort(reverse = True)
valoare = 0
maxCapacitate = capacitate

for sac in saci:
    if sac[2] < capacitate:
        capacitate = capacitate - sac[2]
        valoare = valoare + sac[1]
    else:
        fractie = capacitate / sac[2]
        capacitate = 0
        valoare = valoare + fractie * sac[1]
        break

print(valoare)
with open("obiecte.txt", "r") as file:
    n = int(file.readline())
    obiecte = []
    for i in range(n):
        valoare, greutate = file.readline().split()
        valoare = int(valoare)
        greutate = int(greutate)
        obiecte.append((valoare, greutate))
    capacitate = int(file.readline())
obiecte.sort(key=lambda ob: ob[0] / ob[1], reverse=True)
i = 0
valoare_totala = 0
while capacitate > 0:
    if capacitate < obiecte[i][1]:
        break
    capacitate -= obiecte[i][1]
    valoare_totala += obiecte[i][0]
    i += 1
if capacitate > 0:
    valoare_totala += obiecte[i][0] * (capacitate / obiecte[i][1])
with open("rucsac.txt", "w") as file:
    print(valoare_totala, file=file)
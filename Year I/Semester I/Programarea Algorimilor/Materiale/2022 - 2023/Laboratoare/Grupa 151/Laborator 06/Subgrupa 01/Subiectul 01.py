# a)
def citire_numere(file_name):
    file = open(file_name)
    L = []
    for lines in file.readlines():
        L.append([int(x) for x in lines.split()])
    file.close()
    return L
# print(citire_numere(f))

# b)
def prelucrare_lista(lista):
    lista2 = []

    for i in lista:
        minim = min(i)
        lst = []
        for element in i:
            if element != minim:
                lst.append(element)
        lista2.append(lst)

    minim = min([len(x) for x in lista2])

    for i in range (len(lista2)):
        lista2[i]=lista2[i][:minim]

    return lista2
                
    


linii =  citire_numere("input.txt")
lista = prelucrare_lista(linii)

# c)
for linie in lista:
    print(*linie)

# d)

numere = set()

k = int(input())

for linie in linii:
    for element in linie:
        if len(str(element)) == k:
            numere.add(element)

numere = list(numere)
numere.sort(reverse=True)
print(*numere)

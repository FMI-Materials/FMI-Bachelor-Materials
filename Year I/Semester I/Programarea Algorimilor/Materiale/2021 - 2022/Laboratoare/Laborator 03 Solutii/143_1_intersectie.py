#citim linie cu linie si fiecare linie -o memoram ca set + facem intersectia
f = open("numere_comune.in")
#rez=set() #nu rez={} - dictionarul vid - pt reuniune
rez=set([int(x) for x in f.readline().split()])
for linie in f:
    print(linie.split(" ")) #ramane \n la ultimul cuvant, eventual si cuvinte vide daca sunt mai multe spatii intre numere
    print(linie.split()) #lista contine doar numerele

    m = set([int(x) for x in linie.split()]) #set((int(x) for x in linie.split()))
    #rez = rez & m
    rez &= m
    #rez.intersection_update(m)
print(sorted(rez))  #sorted(rez) => lista
print(*sorted(rez))
f.close()
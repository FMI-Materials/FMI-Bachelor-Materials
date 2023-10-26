#d={multime_litere: lista cuvintelor care au multima literelor egala cu multime_litere}
f = open("litere.in")
d={}
for linie in f:
    for cuv in linie.split():
        multime_litere = frozenset(cuv)
        if multime_litere in d:
            d[multime_litere].append(cuv)
        else:
            d[multime_litere] = [cuv]
        #print(d)
f.close()
print(d)
def cheie(x):
    return len(x),x
for x in sorted(d.keys(), key=len, reverse =True):
    if len(d[x])>=2:
        print(" ".join(sorted(d[x],key=cheie)))

#daca vrem sa sortam dupa un criteriu legat de valori, nu de chei
# - d.items() returneaza lista de  perechi(tupluri) (cheie,valoare)
#d.values()returneaza o lista cu valorile din dictionar
def cheie(x):
    return len(x[1])
for m,ls in sorted(d.items(), key=cheie):
    print(m,ls)
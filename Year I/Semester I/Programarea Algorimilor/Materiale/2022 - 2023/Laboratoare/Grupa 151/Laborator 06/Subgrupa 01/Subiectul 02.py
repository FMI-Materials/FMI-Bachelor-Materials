from copy import deepcopy

# a) Să se memoreze datele din fișier într-o singură structură de date astfel încât să se răspundă cât mai eficient la cerințele de la punctele următoare.
def citire_fisier(filename):
    with open(filename) as fin:
        struct = dict()
        for line in fin.readlines():
            line = line.strip()
            cinema, film, ore = line.split(" % ")
            ore = ore.split()
            if not struct.get(film):
                struct[film] = dict()
            struct[film][cinema] = ore
    return struct

def citire_fisier_2(filename):
    with open(filename) as fin:
        struct = dict()
        for line in fin.readlines():
            line = line.strip()
            cinema, film, ore = line.split(" % ")
            ore = ore.split()
            if not struct.get(cinema):
                struct[cinema] = dict()
            struct[cinema][film] = ore
    return struct

struct = citire_fisier_2("cinema.in")
for film in struct:
    print(f"{film}:{struct[film]}")

# b)
def sterge_ore(structura, cinema, film, ore):
    structura = deepcopy(structura)
    
    if not structura.get(cinema):
        print("Nu exista cinema-ul indicat")
        return
    if not structura[cinema].get(film):
        print("Filmul nu ruleaza in cinema-ul indicat")
        return
    for ora in ore:
        if ora in structura[cinema][film]:
            structura[cinema][film].remove(ora)
    return structura
    
film = input("Filmul: ")
cinema = input("Cinema: ")
orele = input("Orele: ")

print(sterge_ore(struct, cinema, film, [orele]))

# c)
def cinema_film(struct, cinematografe, ora_min, ora_max ):
    filme = []
    for cinema in cinematografe:
        for film in struct[cinema]:
            ore = struct[cinema][film]
            
            lista = []
            for ora in ore:
                if ora_min<=ora and ora<=ora_max :
                    lista.append(ora)
            if len(lista) > 0:
                filme.append((film, cinema, lista))
    filme.sort(key=lambda lst: (lst[0], -len(lst[2])))
    return filme

print(cinema_film(struct, ["Cinema 1","Cinema 2"], "14:00", "22:00"))

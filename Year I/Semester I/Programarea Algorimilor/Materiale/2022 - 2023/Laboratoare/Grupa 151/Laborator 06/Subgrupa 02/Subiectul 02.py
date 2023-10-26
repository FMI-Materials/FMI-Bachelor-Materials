# a
def citire_fisier(filename):
    struct = dict()
    with open(filename) as fin:
        for line in fin.readlines():
            line = line.strip()
            cinema, film, ore = line.split(" % ")
            ore = ore.split()
            if not struct.get(cinema):
                struct[cinema] = dict()
            struct[cinema][film] = ore
    return struct

struct = citire_fisier("cinema.in")
for cin in struct:
    print(f"{cin} : {struct[cin]}")

def pct_b(struct, cinema, film, ore):
    structura = deepcopy(structura)
    if not structura.get(cinema):
        print("Nu exista cinema-ul")
        return
    if not structura[cinema].get(film):
        print("Filmul nu ruleaza in cinema-ul indicat")
        return
    for ora in ore:
        if ora in structura[film][cinema]:
            structura[film][cinema].remove(ora)
    return structura

def pct_c(struct, cinematografe, ora_min, ora_max):
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


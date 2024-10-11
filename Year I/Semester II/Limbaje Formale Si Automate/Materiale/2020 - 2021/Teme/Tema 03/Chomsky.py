# Popescu Paullo Robertto Karloss
# Grupa 131
# CFG -> Forma Normala Chomsky

from copy import deepcopy
from queue import Queue
import re

nouNT = 'M'
tranz = {}


class CFG:
    def __init__(self, neterminale, terminale, S, tranz):
        self.terminale = deepcopy(terminale)
        self.neterminale = deepcopy(neterminale)
        self.tranz = deepcopy(tranz)
        self.S = S


# Functie care ajuta la replace-ul al celui de al n-ulea caracter din string-ul respectiv
def replacement(string, sub, cautat, n):
    unde = [m.start() for m in re.finditer(sub, string)][n - 1]
    inainte = string[:unde]
    dupa = string[unde:]
    dupa = dupa.replace(sub, cautat, 1)
    stringNou = inainte + dupa
    return stringNou


# Etapa 1
# Eliminam lambda productii
def stergeLambda(gramatica):
    # Eliminam startile neterminale care nu ne dau productii
    bun = [N for N in gramatica.tranz.keys()]
    rau = [N for N in gramatica.neterminale if N not in bun]
    gramatica.neterminale = deepcopy(bun)
    for neterminal in gramatica.tranz.keys():
        for i in range(len(gramatica.tranz[neterminal])):
            for rauN in rau:
                if rauN in gramatica.tranz[neterminal][i]:
                    gramatica.tranz[neterminal][i] = gramatica.tranz[neterminal][i].replace(rauN, '')
        gramatica.tranz[neterminal] = list(filter(lambda a: a != '', gramatica.tranz[neterminal]))

    # Daca nu are lambda tranzitii, ne intoarcem
    if '$' not in gramatica.terminale:
        return gramatica

    bun = False  # Ne oprim cand tranzNoua va fi gol(empty)
    while not bun:
        tranzNoua = {}
        for neterminal in gramatica.tranz.keys():
            if '$' in gramatica.tranz[neterminal] and len(gramatica.tranz[neterminal]) == 1:
                for nt in gramatica.tranz.keys():
                    if nt != neterminal:
                        tranzNoua[nt] = deepcopy(gramatica.tranz[nt])
                        for i in range(len(tranzNoua[nt])):
                            if neterminal in tranzNoua[nt][i]:
                                if tranzNoua[nt][i] == neterminal:
                                    tranzNoua[nt][i] = '$'
                                else:
                                    tranzNoua[nt][i] = tranzNoua[nt][i].replace(neterminal, '')
                                    if tranzNoua[nt][i] == '':
                                        tranzNoua[nt][i] = "$"
                gramatica.tranz = deepcopy(tranzNoua)
                # print(gramatica.tranz)
                break
            elif '$' in gramatica.tranz[neterminal] and len(gramatica.tranz[neterminal]) > 1:
                for nt in gramatica.tranz.keys():
                    if nt == neterminal:
                        tranzNoua[nt] = deepcopy(gramatica.tranz[nt])
                        tranzNoua[nt].remove('$')
                        adauga = []
                        for i in range(len(gramatica.tranz[nt])):
                            if nt in gramatica.tranz[nt][i]:
                                # Acum trebuie sa verificam de cate ori apare neterminalul in tranzitia curenta
                                q = Queue()
                                q.put(gramatica.tranz[nt][i])
                                while not q.empty():
                                    curr = q.get()
                                    temp_num = curr.count(neterminal)
                                    if temp_num > 0:
                                        for i in range(1, temp_num + 1):
                                            check = replacement(curr, neterminal, '', i)
                                            if check == '':
                                                check = '$'
                                            if check not in adauga and check not in gramatica.tranz[nt]:
                                                adauga.append(check)
                                                q.put(check)
                        tranzNoua[nt].extend(adauga)
                    else:
                        tranzNoua[nt] = deepcopy(gramatica.tranz[nt])
                        adauga = []
                        for i in range(len(tranzNoua[nt])):
                            if tranzNoua[nt][i] == neterminal:
                                if '$' not in tranzNoua[nt]:
                                    tranzNoua[nt].append('$')
                            elif neterminal in tranzNoua[nt][i]:
                                # Acum trebuie sa verificam de cate ori apare neterminalul in tranzitia curenta
                                q = Queue()
                                q.put(tranzNoua[nt][i])
                                while not q.empty():
                                    curr = q.get()
                                    temp_num = curr.count(neterminal)
                                    if temp_num > 0:
                                        for i in range(1, temp_num + 1):
                                            check = replacement(curr, neterminal, '', i)
                                            if check == '':
                                                check = '$'
                                            if check not in adauga and check not in tranzNoua[nt]:
                                                adauga.append(check)
                                                q.put(check)
                        tranzNoua[nt].extend(adauga)
                gramatica.tranz = deepcopy(tranzNoua)
                # print(gramatica.tranz)
                break
        if tranzNoua == {}:
            bun = True

    return CFG


# Etapa 2
# Eliminarea redenumirilor
def stergeRedenumiri(gramatica):
    # Stergem starile X => X
    for stare in gramatica.tranz.keys():
        if stare in gramatica.tranz[stare]:
            gramatica.tranz[stare].remove(stare)

    # Inlocuim starile X => Y
    bun = False
    while not bun:
        tranzNoua = deepcopy(gramatica.tranz)
        for neterminal in gramatica.tranz.keys():
            for stare in gramatica.tranz[neterminal]:
                if stare in gramatica.neterminale:
                    tranzNoua[neterminal].remove(stare)
                    tranzNoua[neterminal] = list(set(tranzNoua[neterminal]).union(set(gramatica.tranz[stare])))
        if tranzNoua == gramatica.tranz:
            bun = True
        else:
            gramatica.tranz = deepcopy(tranzNoua)

    return gramatica


# Etapa 3
# Eliminam productiile inutile
def stergeProductii_Inutile(gramatica):
    # Vrem sa eliminam mai intai starile care nu sunt accesibile
    q = Queue()
    q.put(gramatica.S)
    checked = [gramatica.S]
    while not q.empty():
        curr = q.get()
        for prod in gramatica.tranz[curr]:
            for stare in prod:
                if stare in gramatica.neterminale and stare not in checked:
                    q.put(stare)
                    checked.append(stare)
    useless = list(set(gramatica.neterminale).difference(set(checked)))
    for neterminal in useless:
        gramatica.neterminale.remove(neterminal)
        del gramatica.tranz[neterminal]
    # print("Aici: ", gramatica.terminale, gramatica.neterminale, gramatica.S, gramatica.tranz)

    # Eliminam starile care sunt infinite
    sterge = []
    for neterminal in gramatica.tranz.keys():
        for prod in gramatica.tranz[neterminal]:
            if neterminal not in prod:
                break
        else:
            sterge.append(neterminal)

    for neterminal in sterge:
        del gramatica.tranz[neterminal]
    for neterminal in gramatica.tranz.keys():
        removeStari = []
        for nt in sterge:
            for prod in gramatica.tranz[neterminal]:
                if nt in prod and prod not in removeStari:
                    removeStari.append(prod)
        gramatica.tranz[neterminal] = list(set(gramatica.tranz[neterminal]).difference(set(removeStari)))

    return gramatica


# Etapa 4
# Adaugare neterminale noi pentru productii ab sau aU
def addNeterminale(gramatica):
    global nouNT
    term_map = {}
    tranzNouaitii = {}
    for neterminal in gramatica.tranz.keys():
        for i in range(len(gramatica.tranz[neterminal])):
            terms = list(set(gramatica.tranz[neterminal][i]).intersection(set(gramatica.terminale)))
            nonterms = list(set(gramatica.tranz[neterminal][i]).intersection(set(gramatica.neterminale)))
            if (terms != [] and nonterms != []) or (nonterms == [] and len(terms) > 1) or (
                    nonterms == [] and len(terms) == 1 and len(gramatica.tranz[neterminal][i]) > 1):
                for t in terms:
                    if t not in term_map:
                        term_map[t] = nouNT
                        tranzNouaitii[nouNT] = [t]
                        gramatica.neterminale.append(nouNT)
                        nouNT = chr(ord(nouNT) + 1)
                    gramatica.tranz[neterminal][i] = gramatica.tranz[neterminal][i].replace(t, term_map[t])
    gramatica.tranz.update(tranzNouaitii)

    return gramatica


# Etapa 5
# Adaugam neterminale pentru productiile cu mai mult de 2 neterminale
def addProductii(gramatica):
    global nouNT
    nt_map = {}
    bun = False
    while not bun:
        tranzNoua = {}
        for neterminal in gramatica.tranz.keys():
            for i in range(len(gramatica.tranz[neterminal])):
                if gramatica.tranz[neterminal][i] not in gramatica.terminale and len(
                        gramatica.tranz[neterminal][i]) > 2:
                    nouaProd = gramatica.tranz[neterminal][i][1:]
                    if nouaProd not in nt_map.keys():
                        nt_map[nouaProd] = nouNT
                        tranzNoua[nouNT] = [nouaProd]
                        gramatica.neterminale.append(nouNT)
                        nouNT = chr(ord(nouNT) + 1)
                    gramatica.tranz[neterminal][i] = gramatica.tranz[neterminal][i].replace(nouaProd, nt_map[nouaProd])
        if tranzNoua != {}:
            gramatica.tranz.update(tranzNoua)
        else:
            bun = True

    return gramatica


with open("date.in") as file:
    # Terminalele
    terminale_num = int(file.readline())
    terminale = file.readline().rstrip().split()

    # Starea de start
    start = file.readline().rstrip()

    # Neterminalele
    neterminale_num = int(file.readline())
    neterminale = file.readline().rstrip().split()

    # Nr. de tranzitii
    n = int(file.readline())
    for i in range(n):
        stare = file.readline().rstrip()
        tranzitii = file.readline().rstrip().split()
        tranz[stare] = tranzitii

CFG = CFG(neterminale, terminale, start, tranz)
print("Initial:", CFG.terminale, CFG.neterminale, CFG.S, CFG.tranz)

# Pasul 1.
# Eliminam lambda tranzitiile
CFG = stergeLambda(CFG)
print("Pasul 1:", CFG.terminale, CFG.neterminale, CFG.S, CFG.tranz)

# Pasul 2.
# Eliminam redenumirile
CFG = stergeRedenumiri(CFG)
print("Pasul 2:", CFG.terminale, CFG.neterminale, CFG.S, CFG.tranz)

# Pasul 3.
# Eliminam productiile inutile
CFG = stergeProductii_Inutile(CFG)
print("Pasul 3:", CFG.terminale, CFG.neterminale, CFG.S, CFG.tranz)

# Pasul 4.
# Adaugare neterminale noi
CFG = addNeterminale(CFG)
print("Pasul 4:", CFG.terminale, CFG.neterminale, CFG.S, CFG.tranz)

# Pasul 5.
# Adaugare neterminale noi pentru productiile cu mai mult de 2 neterminali
CFG = addProductii(CFG)
print("Pasul 5:", CFG.terminale, CFG.neterminale, CFG.S, CFG.tranz)
'''
    Acest program se va rula in terminal si va primi ca argumente numele acestui fisier (tm.py),
un fisier ce contine un turing machine (tm.txt) si un fisier ce contine un sir de input (input_tm.txt).
    Programul va incarca turing machine-ul primit si il va valida sau respinge in cazul in care nu are o
configuratie corecta. Apoi programul va citi un sir de input din fisier si il va accepta sau respinge.

'''

import sys

def get_section(name, l_gen):   # prin aceasta functie se vor transforma sectiunile din fisierul
                                  # tm.txt in liste ce contin datele fiecarei sectiuni
    flag = False
    l_ret = []

    for line in l_gen:
        if line.lower() == name + ":":
            flag = True
            continue
        if line.lower() == "end":
            flag = False
        if flag == True:
            l_ret.append(line)

    return l_ret

def get_tm_from_file(file_name): # functie de prelucreaza fisierul ce contine tm-ul
                                # si il valideaza daca respecta conditiile de functionare
    f = open(file_name, "r")

    l = []

    for line in f:
        line = line.strip()
        if len(line) > 0:
            l.append(line)

    l_states = get_section("states",l)
    l_sigma = get_section("sigma", l)
    l_gamma = get_section("gamma", l)
    l_transitions = get_section("transitions", l)

    # l_states_ex va fi o lista de liste unde fiecare lista din interior contine o stare a
    # turing machine-ului, 0 sau 1 daca este stare de start, 0 sau 1 daca este stare de accept
    # si 0 sau 1 daca este stare de reject

    l_states_ex = []
    for state in l_states:
        state = state.split(",")
        l_aux = [state[0],0,0,0]
        for s in state:
            if s == "S":
                l_aux[1] = 1
            if s == "A":
                l_aux[2] = 1
            if s == "R":
                l_aux[3] = 1
        l_states_ex.append(l_aux)

    # l_states va reprezenta a lista ce contine doar starile
    l = []
    for state in l_states:
        state = state.split(",", maxsplit=1)
        l.append(state[0])

    l_states = l

    # se inlocuieste simbolul '_' cu un blank
    for i in range (len(l_gamma)):
        if l_gamma[i] == '_':
            l_gamma[i] = ' '

    # o tranzitie va fi o lista ce are ca prime 2 elemente partea stanga a unei tranzitii
    # iar urmatoarele 3 elemente partea dreapta a acelei tranzitii

    # toate tranzitiile se vor salva intr-o lista

    l = []
    for trans in l_transitions:
        trans = trans.replace(" = ",",")
        trans = trans.split(",")

        #se inlocuieste simbolul '_' cu un blank
        for t in trans:
            if (t == "_"):
                trans[trans.index("_")] = " "

        # se verifica daca starile din tranzitii sunt valide
        if trans[0] not in l_states:
            print(f"reject: {trans[0]} not a state")
            exit()
        if trans[2] not in l_states:
            print(f"reject: {trans[2]} not a state")
            exit()

        # se verifica daca simbolurile se afla in gamma
        if trans[1] not in l_gamma:
            print(f"reject: {trans[1]} not in gamma")
            exit()
        if trans[3] not in l_gamma:
            print(f"reject: {trans[3]} not in gamma")
            exit()

        # ultimul termen al unei tranzitii trebuie sa fie L sau R
        # pentru ca indica din ce directie sa se aleaga urmatorul element
        # daca nu este, tranzitia nu este valida
        if trans[4] != "L" and trans[4] != "R":
            print(f"reject: not a valid direction")
            exit()
                
        l.append(trans)

    l_transitions = l

    # orice simbol din sigma trebuie sa se afle si in gamma
    for s in l_sigma:
        if s not in l_gamma:
            print(f"reject: {s} in sigma, but not in gamma")
            exit()

    return l_states, l_states_ex, l_sigma, l_gamma, l_transitions

def tm_process(file_name, l_states, l_sigma, l_transitions):

    f = open(file_name, "r")
    input = [s.rstrip('\n') for s in f.readlines()]  # lista cu toate sirurile de input

    for string in input:  # se va lua fiecare sir de input pe rand si se va testa

        print(f"{string}:", end=" ")

        # transformam in lista pentru a le putea parcurge
        string = list(string)

        for s in string: # verificam daca toate simbolurile din sirul de input sunt in sigma
            if s not in l_sigma:
                print(f"reject: input symbol \"{s}\" not in sigma")
                exit()

        string.append(" ")  # se adauga un blank ca element final al listei pentru a simula
                            # banda infinita a unui turing machine

        for state in l_states:  # se va determina starea de start
            if state[1] == 1:
                stare_curenta = state[0]
            if state[2] == 1:
                stare_accept = state[0]
            if state[3] == 1:
                stare_reject = state[0]

        i = 0

        # luam fiecare simbol pe rand pentru a trece prin tranzitii
        # programul va rula pana cand ajunge la o stare finala

        while stare_curenta != stare_accept and stare_curenta != stare_reject:
            # pentru fiecare simbol citi se va gasi tranzitia corespunzatoare
            # din lista de tranzitii
            for trans in l_transitions:
                if trans[0] == stare_curenta and trans[1] == string[i]:
                    stare_curenta = trans[2]
                    string[i] = trans[3]

                    # daca este L, ne vom intoarce simbolul anterior
                    # daca este R, vom citi simbolul urmator
                    if trans[4] == "L":
                        if i >= 0:
                            i = i - 1
                    else:
                        i = i + 1
                    # in momentul in care ajunge intr-o stare de accept sau de reject
                    # procesul se incheie si se afiseaza un mesaj corespunzator
                    if stare_curenta == stare_reject:
                        print("reject")
                    if stare_curenta == stare_accept:
                        print("accept")

#
# main entry
#

l_states, l_states_ex, l_sigma, l_gamma, l_transitions = get_tm_from_file(sys.argv[1])

# afisarea componentelor tm-ului
print(f"Starile TM-ului sunt: {l_states}")
print(f"Alfabetul sigma este: {l_sigma}")
print(f"Alfabetul gamma este: {l_gamma}")
print(f"Tranzitiile TM-ului sunt: {l_transitions}\n")

tm_process(sys.argv[2], l_states_ex, l_sigma, l_transitions)
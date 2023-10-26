'''
    Acest program se va rula in terminal si va primi ca argumente numele acestui fisier (dfa.py),
un fisier ce contine un automat finit determinist (dfa.txt) si un fisier ce contine unul sau mai
multe siruri de input (input_dfa.txt).
    Programul va incarca dfa-ul primit si il va valida sau respinge in cazul in care nu are o
configuratie corecta. Apoi programul va citi cate un sir de input din fisier si il va accepta sau respinge.

'''

import sys

def get_section(name, l_gen): # prin aceasta functie se vor transforma sectiunile din fisierul
                              # dfa.txt in liste ce contin datele fiecarei sectiuni
    flag = False
    l_ret = []

    for line in l_gen:
        if line == name + ":":
            flag = True
            continue
        if line == "end":
            flag = False
        if flag == True:
            l_ret.append(line)

    return l_ret

def get_dfa_from_file (file_name): # functie ce incarca si valideaza (sau respinge) fisierul dfa.txt
    f = open(file_name,"r")
    l_gen = []

    for line in f:
        line = line.strip().lower()
        if len(line) > 0 and line[0] != "#":
            l_gen.append(line)

    l_sigma = get_section("sigma", l_gen)               # lista ce contine alfabetul
    l_states = get_section("states", l_gen)             # lista starilor din dfa
    l_transitions = get_section("transitions", l_gen)   # lista tranzitiilor

    l_states_ex = []
    valid_start = 0
    for s in l_states:
        tmp = s.split(",")
        is_start_state = 0
        is_final_state = 0

        for entry in tmp[1:]:
            if entry == "f":
                is_final_state = 1
            if entry == "s":
                is_start_state = 1
                valid_start = 1

        l_states_ex.append([tmp[0], is_start_state, is_final_state])

    # l_states_ex va fi o lista de liste unde fiecare lista din interior contine o stare a
    # dfa-ului, 0 sau 1 daca este stare de start, 0 sau 1 daca este stare finala

    if valid_start == 0:
        print("reject (doesn't have a start state)") # un dfa trebuie sa aiba o stare de start
        exit()

    l = []
    for state in l_states:
        state = state.split(",", maxsplit=1);
        l.append(state[0])

    l_states = l # l_states este o lista ce contine doar starile

    if len(l_sigma) == 0 or len(l_states) == 0 or len(l_transitions) == 0:
        print("reject (section is missing)")
        exit()
    # daca o sectiune lipseste atunci nu avem un dfa valid

    l = [] # prelucram lista de tranzitii intr-o lista de liste
    for trans in l_transitions:
        trans = trans.split(',')
        l.append(trans)

    l_transitions = l

    for trans in l_transitions:
        if trans[0] not in l_states or trans[1] not in l_sigma or trans[2] not in l_states:
            print(f" reject (transition {trans} not valid)")
            exit()
    # verificam daca tranzitiile sunt valide

    return l_sigma,l_states, l_states_ex,l_transitions

def dfa_process (file_name, l_sigma, l_states, l_trans): # functia care valideaza fiecare input din fisier
    f = open(file_name, "r")
    s = [s.rstrip('\n') for s in f.readlines()] # lista cu toate sirurile de input

    for string in s: # se va lua fiecare sir de input pe rand si se va testa

        print (f"{string}:", end = " ")
        for i in range(len(l_states)):          # se determina starea de start
            if l_states[i][1] == 1:
                stare_curenta = l_states[i][0]

        valid = 1
        for x in string:                        # se va trece prin fiecare simbol din sirul de input
            if x in l_sigma:                    # urmand tranzitiile dfa-ului
                for trans in l_trans:
                    if x == trans[1] and stare_curenta == trans[0]:
                        stare_curenta = trans[2]
                        break
            else:
                valid = 0

        if valid == 0:                          # va afisa o eroare daca se gaseste un simbol ce nu e in sigma
            print("reject (input not in sigma)")
            exit()

        valid = 0
        for state in l_states:                  # se verifica daca ultima stare in care am ajuns
                                                # este sau nu stare finala
            if stare_curenta == state[0] and state[2] == 1:
                print("accept")
                valid = 1

        if valid == 0:                          # daca nu este stare finala atunci dfa-ul nu accepta acest sir
            print("reject (not final state)")

#
# main entry
#

l_sigma, l_states,l_states_ex, l_transitions = get_dfa_from_file(sys.argv[1])

# afisarea componentelor dfa-ului
print(f"Alfabetul DFA-ului este: {l_sigma}")
print(f"Starile DFA-ului sunt: {l_states}")
print(f"Tranzitiile DFA-ului sunt: {l_transitions}\n")

dfa_process(sys.argv[2],l_sigma,l_states_ex,l_transitions)
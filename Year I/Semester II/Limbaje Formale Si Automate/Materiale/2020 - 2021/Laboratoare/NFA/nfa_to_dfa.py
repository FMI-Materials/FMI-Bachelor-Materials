'''
    Acest program se va rula in terminal si va primi ca argumente numele acestui fisier (nfa_to_dfa.py),
un fisier ce contine un automat finit nondeterminist (nfa.txt) si un fisier ce contine unul sau mai
multe siruri de input (input_nfa.txt).
    Programul va incarca nfa-ul primit il va converti intr-un dfa si il va valida sau il va respinge in
cazul in care nu are o configuratie corecta. Apoi programul va citi cate un sir din fisierul de input si
il va accepta sau respinge.

'''

import sys

def get_section(name, l_gen): # prin aceasta functie se vor transforma sectiunile din fisierul
                              # nfa.txt in liste ce contin datele fiecarei sectiuni
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

def get_subsets(fullset):   # functia va primi o lista de elemente si va
                            # returna o lista cu toate submultime
    l = list(fullset)
    subsets = []

    for i in range (2**len(l)):
        subset = []
        for k in range (len(l)):
          if i & 1<<k:
            subset.append(l[k])
        subsets.append(subset)

    return subsets

def get_nfa_from_file (file_name): # functie ce incarca si valideaza (sau respinge) fisierul nfa.txt
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
    # nfa-ului, 0 sau 1 daca este stare de start, 0 sau 1 daca este stare finala

    if valid_start == 0:
        print("reject (doesn't have a start state)")
        exit()

    l = []
    for state in l_states:
        state = state.split(",", maxsplit = 1)
        l.append(state[0])

    l_states = l # l_states este o lista ce contine doar starile

    if len(l_sigma) == 0 or len(l_states) == 0 or len(l_transitions) == 0:
        print("reject (section is missing)")
        exit()
    # daca o sectiune lipseste atunci nu avem un dfa valid

    l = []  # prelucram lista de tranzitii intr-o lista de liste
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

def convert_nfa_to_dfa (l_sigma, l_states, l_states_ex, l_transitions): # functia converteste nfa-ul in dfa
    l_states = get_subsets(l_states)
    l_states.pop(0)

    final = [] # lista starilor finale nfa
    for state in l_states_ex:
        if state[1] == 1:
            start = state[0] # starea de start din nfa
        if state[2] == 1:
            final.append(state[0])

    l_ex = []

    for state in l_states:
        l = []
        l.append(",".join(state))

        if start == l[0]: # marcheaza starea de start din dfa
            l.append(1)
        else:
            l.append(0)

        test = 0 # marcheaza starile finale din dfa
        for fstate in final:
            if fstate in l[0]:
                test = 1
                break

        l.append(test)
        l_ex.append(l)

    l_states_ex = l_ex
    l_states = []

    for state in l_states_ex:
        l_states.append(state[0])

    l_trans = []

    for state in l_states:
        for sigma in l_sigma:
            l = []
            states = []
            for s in state.split(","):
                for trans in l_transitions:
                    if s == trans[0] and sigma == trans[1]:
                        states.append(trans[2])
            if len(states) != 0:
                l.append(state)
                l.append(sigma)
                states.sort()
                states = ",".join(states)
                l.append(states)
                l_trans.append(l)

    return l_sigma, l_states, l_states_ex, l_trans

def dfa_process (file_name, l_sigma, l_states, l_trans):

    f = open(file_name, "r")
    s = [s.rstrip('\n') for s in f.readlines()]  # lista cu toate sirurile de input

    for string in s:  # se va lua fiecare sir de input pe rand si se va testa

        print(f"{string}:", end=" ")

        for i in range(len(l_states)):
            if l_states[i][1] == 1:
                stare_curenta = l_states[i][0]

        valid = 1
        for x in string:
            if x in l_sigma:
                for trans in l_trans:
                    if x == trans[1] and stare_curenta == trans[0]:
                        stare_curenta = trans[2]
                        break
            else:
                valid = 0

        if valid == 0:
            print("reject (input not in sigma)")
            exit()

        valid = 0
        for state in l_states:
            if stare_curenta == state[0] and state[2] == 1:
                print("accept")
                valid = 1

        if valid == 0:
            print("reject (not final state)")

#
# main entry
#

l_sigma, l_states, l_states_ex, l_transitions = get_nfa_from_file(sys.argv[1])

# afisarea componentelor nfa-ului
print(f"Alfabetul DFA-ului este: {l_sigma}")
print(f"Starile DFA-ului sunt: {l_states}")
print(f"Tranzitiile DFA-ului sunt: {l_transitions}\n")

l_sigma_dfa, l_states_dfa, l_states_ex_dfa, l_transitions_dfa = convert_nfa_to_dfa(l_sigma, l_states, l_states_ex, l_transitions)

dfa_process(sys.argv[2], l_sigma_dfa, l_states_ex_dfa, l_transitions_dfa)

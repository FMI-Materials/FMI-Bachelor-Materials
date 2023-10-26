'''
    Acest program se va rula in terminal si va primi ca argumente numele acestui fisier (cfg.py) si
un fisier ce contine un context-free grammar (cfg.txt).
    Programul va incarca cfg-ul primit si il va valida sau respinge in cazul in care nu are o
configuratie corecta. Apoi programul va genera random in terminal 10 siruri care pot fi generate din acest cfg.

'''

import random
import sys

def get_section(name, l_gen):   # prin aceasta functie se vor transforma sectiunile din fisierul
                                # cfg.txt in liste ce contin datele fiecarei sectiuni
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

def get_cfg_from_file (file_name): # functie ce incarca si valideaza cfg-ul
    f = open(file_name,"r")
    l_gen = []

    for line in f:
        line = line.strip()
        if len(line) > 0:
            l_gen.append(line)

    l_variables = get_section("variables", l_gen)
    l_terminals = get_section("terminals", l_gen)
    l_rules = get_section("rules", l_gen)

    l = []
    for rule in l_rules:
        l.append(rule.split("="))

    l_rules = l

    # verifica daca regulile sunt scrise corect (daca exista toate variabilele
    # si daca terminalele sunt valide)
    for rule in l_rules:
        if rule[0] not in l_variables:
            print(f"error: variable \"{rule[0]}\" doesn't exist")
            exit()
        for s in list(rule[1]):
            if s not in l_variables and s not in l_terminals:
                print(f"error: terminal \"{s}\" doesn't exit")
                exit()

    # se marcheaza variabila de start
    start  = l_variables[0]

    # verifica daca multimea de terminale si multimea de variabile sunt diferite
    for s in l_terminals:
        if s in l_variables:
            print("error: terminals and variables must be distinct")
            exit()

    return start, l_variables, l_terminals, l_rules

def cfg_process(start, variables, terminals, rules):
    n = 0

    #toate sirurile generate vor fi puse intr-o lista
    l_gen = []

    # se vor genera exact 10 siruri
    while n < 10:
        # se va incepe cu variabila de start
        string = start

        # va rula atata timp cat mai exista variabile in sirul generat
        # deoarece un sir corect se format doar din terminale
        while len(set(variables).intersection(set(list(string)))) != 0:

            # toate regulile care pot fi aplicate la momentul curent se pun intr-o lista
            l = []
            for rule in rules:
                if rule[0] in string:
                    l.append(rule)

            # se alege la intamplare o regula si se foloseste
            random_rule = random.choice(l)
            string = string.replace(random_rule[0], random_rule[1])
            while "_" in string:
                string = string.replace("_","")

        l_gen.append(string)
        n = n + 1

    return l_gen
#
# main entry
#

start, l_variables, l_terminals, l_rules = get_cfg_from_file(sys.argv[1])

# afisarea componentelor dfa-ului
print(f"Variabila de start este: {start}")
print(f"Variabilele sunt: {l_variables}")
print(f"Terminalele sunt: {l_terminals}")
print(f"Regulile sunt: {l_rules}")

#generarea string-urilor
l = cfg_process(start, l_variables, l_terminals, l_rules)
print(f"String-urile generate sunt: {l}")
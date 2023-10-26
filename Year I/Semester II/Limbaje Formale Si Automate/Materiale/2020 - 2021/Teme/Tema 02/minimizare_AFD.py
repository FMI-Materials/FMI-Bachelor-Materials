# Proiect LFA - Laborator3 - MINIMIZARE DFA


#   THE MEANING OF THE VARIABLES WE USED
#
# start - start node ( initial state)
# alphabet - sigma from AFD
# nodes - set of the states
# final_nodes - set of the final nodes
# transition - edges of the AFD


start = None
transition = []
alphabet, nodes, final_nodes = set(), set(), set()


def iscomment(line):
    for caracter in line:
        if caracter == '#':
            return 1
        if caracter != '\n' and caracter != '\t' and caracter != ' ':
            return 0


def is_blank(line):
    for x in line:
        if x != ' ':
            return 0
    else:
        return 0
    return 1


def validate_input_file(nume_fisier):
    f = open(nume_fisier, "r")
    sigma, states, transitions = False, False, False
    global transition, alphabet, nodes, final_nodes, start
    transition = []
    for line in f:
        while line == '\n' or iscomment(line):
            try:
                line = f.readline()
            except EOFError:
                return 0
        if line == "":
            break
        line = line.strip()
        if line == "Sigma:":
            sigma = True
            try:
                line = f.readline()
            except EOFError:
                return 0

            while line != "End" and line != "End\n":
                if len(line) == 0 and is_blank(line) == 0:
                    return 0
                if not iscomment(line) and line != "\n" and is_blank(line) == 0:
                    line = line.strip()
                    if "States" in line or "Transitions" in line or "Sigma" in line:
                        return 0
                    elif (line is None):
                        return 0
                    elif len(line) > 1 or (not line.isalpha()):
                        return 0
                    alphabet.add(line)
                try:
                    line = f.readline()
                except EOFError:
                    return 0

        elif line == "States:":
            states = True
            start = None
            try:
                line = f.readline()
            except EOFError:
                return 0
            while line != "End\n" and line != "End":
                if len(line) == 0 and is_blank(line) == 0:
                    return 0
                if not iscomment(line) and line != "\n" and is_blank(line) == 0:
                    line = line.strip()
                    if "States" in line or "Transitions" in line or "Sigma" in line:
                        return 0
                    elif (line is None):
                        return 0
                    if ',' in line:
                        position_of_comma = line.find(",")
                        node = line[:position_of_comma]
                        node = int(node)
                        if line[position_of_comma + 1] != 'F' and line[position_of_comma + 1] != 'S':
                            return 0
                        if line[position_of_comma + 1] == 'S':
                            if start is None:
                                start = node
                            else:
                                return 0
                        if line[position_of_comma + 1] == 'F':
                            final_nodes.add(node)
                        if position_of_comma + 2 < len(line):
                            if line[position_of_comma + 2] == ',':
                                position_of_comma += 2
                                if position_of_comma + 1 >= len(line):
                                    return 0
                                if line[position_of_comma + 1] != 'F' and line[position_of_comma + 1] != 'S':
                                    return 0
                                if line[position_of_comma + 1] == 'S':
                                    if start is None:
                                        start = node
                                    else:
                                        return 0
                                if line[position_of_comma + 1] == 'F':
                                    final_nodes.add(node)
                            else:
                                return 0
                        nodes.add(node)
                    else:
                        nodes.add(int(line))
                try:
                    line = f.readline()
                except EOFError:
                    return 0
        elif line == "Transitions:":
            transitions = True
            state_1, state_2, letter = 0, 1, ""
            try:
                line = f.readline()
            except EOFError:
                return 0
            while line != "End\n" and line != "End":
                if len(line) == 0 and is_blank(line) == 0:
                    return 0
                if line != "\n" and not iscomment(line) and is_blank(line) == 0:
                    line = line.strip()
                    if ',' in line:
                        if ' ' in line:
                            return 0
                        else:
                            if line.count(',') != 2 or line[1] != ',' or line[-2] != ',':
                                return 0
                            line = line.replace(',', ' ')
                            state_1, letter, state_2 = line.split(maxsplit=2)
                            state_1, state_2 = int(state_1), int(state_2)
                            if states == True and (state_1 not in nodes or state_2 not in nodes):
                                return 0
                            if sigma == True and letter not in alphabet:
                                return 0
                            for x in transition:
                                if x[0] == state_1 and x[1] == letter:
                                    return 0
                            transition.append((state_1, letter, state_2))
                    elif "States" in line or "Transitions" in line or "Sigma" in line:
                        return 0
                    elif (line is None):
                        return 0
                try:
                    line = f.readline()
                except EOFError:
                    return 0
        else:
            return 0
    if sigma and transitions and states:
        for edge in transition:
            if edge[0] not in nodes or edge[2] not in nodes:
                return 0
            elif edge[1] not in alphabet:
                return 0
        return 1
    else:
        return 0


def from_list_dict(transition):
    dictionar = {}
    for tuplu in transition:
        t = (int(tuplu[0]), tuplu[1])
        dictionar[t] = int(tuplu[2])
    return dictionar


def AFD_minimal_Myhill():
    global transition, start, alphabet, nodes, final_nodes
    # transformam tranzitiile in dictionat de tipul dict[ ( nod , caracter) ]= nod final pentru a ne fi mai usor
    dictionar_transition = from_list_dict(transition)
    n = len(nodes)
    matrice = [[0 for i in range(n)] for j in range(n)]
    for i in range(n):
        for j in range(i):
            if (i in final_nodes and j not in final_nodes) or (i not in final_nodes and j in final_nodes):
                matrice[i][j] = 1
    ok = 1
    while ok == 1:
        ok = 0
        for i in range(n):
            for j in range(i):
                if matrice[i][j] == 0:  # daca elementul nu e marcat
                    for caracter in alphabet:
                        state1 = dictionar_transition[(i, caracter)]
                        state2 = dictionar_transition[(j, caracter)]
                        if matrice[state1][state2] == 1:
                            matrice[i][j] = 1
                            ok = 1
                            break
    lista_multimi = []
    k = 1
    vizitati = [0 for i in range(n)]
    for i in range(n):
        for j in range(i):
            if matrice[i][j] == 0:
                ok = 0
                for contor in range(len(lista_multimi)):
                    if i in lista_multimi[contor] or j in lista_multimi[contor]:
                        lista_multimi[contor].add(i)
                        lista_multimi[contor].add(j)
                        ok = 1
                        if vizitati[i] == 0:
                            vizitati[i] = vizitati[j]
                        else:
                            vizitati[j] = vizitati[i]

                if ok == 0:
                    m = set()
                    m.add(i)
                    m.add(j)
                    lista_multimi.append(m)
                    vizitati[i], vizitati[j] = k, k
                    k = k + 1

    for i in range(n):
        if vizitati[i] == 0:
            m = set()
            m.add(i)
            lista_multimi.append(m)
            vizitati[i] = k
            k = k + 1

    # vectorul de vizitati e ca o partitie si ne spune un nod in ce multime este

    transition_new = {}
    final_nodes_new = set()
    for noduri_grupate in lista_multimi:
        for caracter in alphabet:
            next_states = 0
            for nod in noduri_grupate:
                if nod == start:
                    start_new = vizitati[nod]
                if nod in final_nodes:
                    final_nodes_new.add(vizitati[nod])
                next_states = dictionar_transition[(nod, caracter)]
                k = vizitati[nod]
            for multime in lista_multimi:
                if next_states in multime:
                    t = (k, caracter)
                    transition_new[t] = vizitati[next_states]
    print("alphabet : ", end=" ")
    print(alphabet)
    print("transition : ", end=" ")
    print(transition_new)
    print("start node:", end=" ")
    print(start_new)
    print("final nodes:", end=" ")
    print(final_nodes_new)


import sys

file = sys.argv[1]
if (validate_input_file(file) == 1):
    AFD_minimal_Myhill()

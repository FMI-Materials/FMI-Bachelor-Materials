# Proiect LFA - Laborator2 - Validare cuvant NFA


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
                            if sigma == True and letter not in alphabet and letter!=chr(949):
                                return 0
                                #chr de 949 inseamna epsilon
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
            elif edge[1] not in alphabet and edge[1]!=chr(949):
                return 0
        return 1
    else:
        return 0

def validate_word_AFN(stare, word):
    if len(word) == 0:
        if stare in final_nodes:
            return 1
        else:
            return 0
    for edge in transition:
        state_1, letter, state_2 = edge[0], edge[1], edge[2]
        if state_1 == stare and word[0] == letter:
            ok = validate_word_AFN(state_2, word[1:])
            if ok == 1:
                return 1
    return 0

import sys

file,word = sys.argv[1],sys.argv[2]

if validate_input_file(file)==1:
    print(validate_word_AFN(start, word))
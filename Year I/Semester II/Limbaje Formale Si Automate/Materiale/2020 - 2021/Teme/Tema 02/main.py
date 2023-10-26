# Proiect LFA - Laborator1+2 - Validare fisier input + Validare cuvant


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

def finish(cod):
    print("INPUT FILE IS INVALID BECAUSE : ", end="")
    if cod == 1:
        print("One block doesn't have an 'End'")
    elif cod == 2:
        print("The file ended without all requested datas")
    elif cod == 3:
        print("The alphabet must contain only characters")
    elif cod == 4:
        print("States can have only S(start) or F(finish) attributes")
    elif cod == 5:
        print("This file contains two start states")
    elif cod == 6:
        print("State attribute missing")
    elif cod == 7:
        print("Format not accepted for States block")
    elif cod == 8:
        print("Transitions description cannot contain spaces")
    elif cod == 9:
        print("Format not accepted for Transitions block")
    elif cod == 10:
        print("A state from Transitions doesn't belong to nodes")
    elif cod == 11:
        print("A character from Transitions doesn't belong to Sigma")
    elif cod == 12:
        print("This file contains an unknown block")
    elif cod == 13:
        print("This file doesn't contain all requested blocks")

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
                finish(1)
                return 0
        if line == "":
            break
        line = line.strip()
        if line == "Sigma:":
            sigma = True
            try:
                line = f.readline()
            except EOFError:
                finish(1)
                return 0
            line = line.strip()
            while line != "End" and line != "End\n":
                if len(line) == 0 and is_blank(line) == 0:
                    finish(1)
                    return 0
                if not iscomment(line) and line != "\n" and is_blank(line) == 0:
                    if "States" in line or "Transitions" in line or "Sigma" in line:
                        finish(1)
                        return 0
                    elif (line is None):
                        finish(2)
                        return 0
                    elif len(line) > 1 or (not line.isalpha()):
                        finish(3)
                        return 0
                    alphabet.add(line)
                try:
                    line = f.readline()
                except EOFError:
                    finish(1)
                    return 0
                line = line.strip()
        elif line == "States:":
            states = True
            start = None
            try:
                line = f.readline()
            except EOFError:
                finish(1)
                return 0
            while line != "End\n" and line != "End":
                if len(line) == 0 and is_blank(line) == 0:
                    finish(1)
                    return 0
                if not iscomment(line) and line != "\n" and is_blank(line) == 0:
                    line = line.strip()
                    if "States" in line or "Transitions" in line or "Sigma" in line:
                        finish(1)
                        return 0
                    elif (line is None):
                        finish(2)
                        return 0
                    if ',' in line:
                        position_of_comma = line.find(",")
                        node = line[:position_of_comma]
                        if line[position_of_comma + 1] != 'F' and line[position_of_comma + 1] != 'S':
                            finish(4)
                            return 0
                        if line[position_of_comma + 1] == 'S':
                            if start is None:
                                start = node
                            else:
                                finish(5)
                                return 0
                        if line[position_of_comma + 1] == 'F':
                            final_nodes.add(node)
                        if position_of_comma + 2 < len(line):
                            if line[position_of_comma + 2] == ',':
                                position_of_comma += 2
                                if position_of_comma + 1 >= len(line):
                                    finish(6)
                                    return 0
                                if line[position_of_comma + 1] != 'F' and line[position_of_comma + 1] != 'S':
                                    finish(4)
                                    return 0
                                if line[position_of_comma + 1] == 'S':
                                    if start is None:
                                        start = node
                                    else:
                                        finish(5)
                                        return 0
                                if line[position_of_comma + 1] == 'F':
                                    final_nodes.add(node)
                            else:
                                finish(7)
                                return 0
                        nodes.add(node)
                    else:
                        nodes.add(line)
                try:
                    line = f.readline()
                except EOFError:
                    finish(1)
                    return 0
        elif line == "Transitions:":
            transitions = True
            state_1, state_2, letter = "", "", ""
            try:
                line = f.readline()
            except EOFError:
                finish(1)
                return 0
            while line != "End\n" and line != "End":
                if len(line) == 0 and is_blank(line) == 0:
                    finish(1)
                    return 0
                if line != "\n" and not iscomment(line) and is_blank(line) == 0:
                    line = line.strip()
                    if ',' in line:
                        if ' ' in line:
                            finish(8)
                            return 0
                        else:
                            if line.count(',') != 2 or line[1] != ',' or line[-2] != ',':
                                finish(9)
                                return 0
                            line = line.replace(',', ' ')
                            state_1, letter, state_2 = line.split(maxsplit=2)
                            if states == True and (state_1 not in nodes or state_2 not in nodes):
                                finish(10)
                                return 0
                            if sigma == True and letter not in alphabet:
                                finish(11)
                                return 0
                            transition.append((state_1, letter, state_2))
                    elif "States" in line or "Transitions" in line or "Sigma" in line:
                        finish(1)
                        return 0
                    elif (line is None):
                        finish(2)
                        return 0
                try:
                    line = f.readline()
                except EOFError:
                    finish(1)
                    return 0
        else:
            finish(12)
            return 0
    if sigma and transitions and states:
        for edge in transition:
            if edge[0] not in nodes or edge[2] not in nodes:
                finish(10)
                return 0
            elif edge[1] not in alphabet:
                finish(11)
                return 0
        print("INPUT FILE IS VALID")
        return 1
    else:
        finish(13)
        return 0

def validate_word(word):
    actual_state = start
    ok = True
    for character in word:
        found = False
        for edge in transition:
            state_1, letter, state_2 = edge[0], edge[1], edge[2]
            if state_1 == actual_state and character == letter:
                actual_state = state_2
                found = True
                break
        if found == False:
            ok = False
            break
    if ok == True and actual_state in final_nodes:
        print("WORD ACCEPTED")
    else:
        print("WORD REJECTED")

import sys

file,word = sys.argv[1],sys.argv[2]

if validate_input_file(file)==1:
    validate_word(word)

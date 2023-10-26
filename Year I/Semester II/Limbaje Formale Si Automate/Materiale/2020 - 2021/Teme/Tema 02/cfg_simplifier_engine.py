
start = None
epsilon = None
terminals = set()
nonTerminals = set()
productions = dict()


def finish(cod):
    print("INPUT FILE IS INVALID BECAUSE : ", end="")
    if cod == 1:
        print("One block doesn't have an 'End'")
    elif cod == 2:
        print("The file ended without all requested datas")
    elif cod == 3:
        print("The Start must contain only characters")
    elif cod == 4:
        print("The Epsilon must be a character")
    elif cod == 5:
        print("The Terminals must contain only lowercase characters")
    elif cod == 6:
        print("The Nonterminals must contain only uppercase characters")
    elif cod == 7:
        print("Format not accepted for Productions block")


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
    Start, Epsilon, Terminals, NonTerminals, Productions = False, False, False, False, False
    global start, epsilon, terminals, nonTerminals, productions
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
        if line == "Start:":
            Start = True
            try:
                line = f.readline()
            except EOFError:
                finish(1)
                return 0
            while line != "End" and line != "End\n":
                if len(line) == 0 and is_blank(line) == 0:
                    finish(1)
                    return 0
                if not iscomment(line) and line != "\n" and is_blank(line) == 0:
                    line = line.strip()
                    if "Epsilon" in line or "Terminals" in line or "Nonterminals" in line or "Productions" in line or "Start" in line:
                        finish(1)
                        return 0
                    elif (line is None):
                        finish(2)
                        return 0
                    elif len(line) > 1 or (not line.isalpha()):
                        finish(3)
                        return 0
                    start = line
                try:
                    line = f.readline()
                except EOFError:
                    finish(1)
                    return 0
        elif line == "Epsilon:":
            Epsilon = True
            try:
                line = f.readline()
            except EOFError:
                finish(1)
                return 0
            while line != "End" and line != "End\n":
                if len(line) == 0 and is_blank(line) == 0:
                    finish(1)
                    return 0
                if not iscomment(line) and line != "\n" and is_blank(line) == 0:
                    line = line.strip()
                    if "Epsilon" in line or "Terminals" in line or "Nonterminals" in line or "Productions" in line or "Start" in line:
                        finish(1)
                        return 0
                    elif (line is None):
                        finish(2)
                        return 0
                    elif len(line) > 1:
                        finish(4)
                        return 0
                    epsilon = line
                try:
                    line = f.readline()
                except EOFError:
                    finish(1)
                    return 0
        elif line == "Terminals:":
            Terminals = True
            try:
                line = f.readline()
            except EOFError:
                finish(1)
                return 0
            while line != "End" and line != "End\n":
                if len(line) == 0 and is_blank(line) == 0:
                    finish(1)
                    return 0
                if not iscomment(line) and line != "\n" and is_blank(line) == 0:
                    line = line.strip()
                    if "Epsilon" in line or "Terminals" in line or "Nonterminals" in line or "Productions" in line or "Start" in line:
                        finish(1)
                        return 0
                    elif (line is None):
                        finish(2)
                        return 0
                    elif len(line) > 1 or (not line.isalpha()) or (line.lower()!=line):
                        finish(5)
                        return 0
                    terminals.add(line)
                try:
                    line = f.readline()
                except EOFError:
                    finish(1)
                    return 0
        elif line == "Nonterminals:":
            NonTerminals = True
            try:
                line = f.readline()
            except EOFError:
                finish(1)
                return 0
            while line != "End" and line != "End\n":
                if len(line) == 0 and is_blank(line) == 0:
                    finish(1)
                    return 0
                if not iscomment(line) and line != "\n" and is_blank(line) == 0:
                    line = line.strip()
                    if "Epsilon" in line or "Terminals" in line or "Nonterminals" in line or "Productions" in line or "Start" in line:
                        finish(1)
                        return 0
                    elif (line is None):
                        finish(2)
                        return 0
                    elif len(line) > 1 or (not line.isalpha()) or (line.upper()!=line):
                        finish(6)
                        return 0
                    nonTerminals.add(line)
                try:
                    line = f.readline()
                except EOFError:
                    finish(1)
                    return 0
        elif line == "Productions:":
            Productions = True
            string1, string2 = "", ""
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
                    if "Epsilon" in line or "Terminals" in line or "Nonterminals" in line or "Productions" in line or "Start" in line:
                        finish(1)
                        return 0
                    elif (line is None):
                        finish(2)
                        return 0
                    else:
                        string1, string2 = line.split(maxsplit=1)
                        productions[string1] = string2
                try:
                    line = f.readline()
                except EOFError:
                    finish(1)
                    return 0
        else:
            finish(12)
            return 0
    if Start and Epsilon and Terminals and NonTerminals and Productions:
        for prod in productions.keys():
            if prod not in nonTerminals and prod != start:
                finish(7)
                return
            string2 = productions[prod]
            for x in string2:
                if (x not in terminals) and (x not in nonTerminals) and (x != "|") and (x != " ") and (x != start) and (x != epsilon):
                    finish(7)
                    return
        print("INPUT FILE IS VALID")
        return 1
    else:
        finish(13)
        return 0

file = input()
validate_input_file(file)

productions2 = {}
for x in nonTerminals:
    productions2[x] = set()

for var in productions.keys():
    cnt = productions[var].find('|')
    if cnt == -1:
        productions2[var].add(productions[var])
    else:
        last = 0
        while cnt != -1:
            productions2[var].add(productions[var][last:cnt])
            last = cnt +1
            cnt = productions[var].find('|',cnt+1)
        productions2[var].add(productions[var][last:])
productions = productions2


#Pas 1: eliminam productiile nule

productions2 = productions
flag = False

while not flag:  #cat timp am mai intalnit o noua productie nula
    for var in nonTerminals:
        if var != start:
            if '0' in productions[var]:  #am gasit o productie nula, trebuie sa o inlocuim peste tot
                flag = True
                for cheie in productions.keys():
                    if cheie != var:
                        setnou = productions[cheie].copy()
                        set2 = setnou.copy()
                        for elem in set2:
                            if var in elem:
                                for i in range(len(elem)):
                                    if elem[i] == var:
                                        if elem[:i] + elem[i + 1:] == '':
                                            setnou.add('0')
                                        else:
                                            setnou.add(elem[:i] + elem[i + 1:])
                        while setnou != set2:
                            set2 = setnou.copy()
                            for elem in set2:
                                if var in elem:
                                    for i in range(len(elem)):
                                        if elem[i] == var:
                                            if elem[:i] + elem[i+1:] == '':
                                                setnou.add('0')
                                            else:
                                                setnou.add(elem[:i] + elem[i + 1:])
                        productions2[cheie] = setnou.copy()
                productions[var].remove('0')
    if flag:
        flag = False
    else:
        break

productions = productions2

#Pas2 : eliminam productiile unitare

productions2 = {}
visited = {}
for var in nonTerminals:
    productions2[var] = set()
    visited[var] = False
for var in productions.keys():
    for elem in productions[var]:
        if elem not in nonTerminals:
            productions2[var].add(elem)

def adaugare(nod, val):
    visited[val] = True
    for x in productions[val]:
        if x not in nonTerminals:
            productions2[nod].add(x)
        else:
            if visited[x] == False:
                adaugare(nod, x)
    visited[val] = False


for var in productions.keys():
    for elem in productions[var]:
        if elem in nonTerminals:
            visited[var] = True
            adaugare(var,elem)

productions = productions2


#Pas 3.1: eliminam variabilele in care nu se ajunge niciodata

valid = {}
for var in nonTerminals:
    valid[var] = False
for x in productions.values():
    for elem in x:
        for var in valid.keys():
            if var in elem:
                valid[var] = True
valid[start] = True
for var in valid.keys():
    if valid[var] == False:
        if productions[var]:
            del productions[var]
            nonTerminals.remove(var)
#print(productions)
#print(nonTerminals)

#Pas 3.2: eliminam productiile infinite

valid = {}
for var in nonTerminals:
    valid[var] = False
for var in productions.keys():
    for elem in productions[var]:
        if var not in elem:
            valid[var] = True
            continue

valid[start] = True
#print(valid)

#in valid avem True variabilele care se duc in altceva inafara de ele
for x in valid:
    if valid[x] == False:
        del productions[x]
        nonTerminals.remove(x)

#print(productions)
#print(valid)
#print (nonTerminals)
#ne mai ramane de scos niste productii din dreapta dupa ce am eliminat variabile
def prodValida(cuv):
    for i in range(len(cuv)):
        if cuv[i]>='A' and cuv[i]<='Z':
            if cuv[i] not in nonTerminals:
                return False
    return True

productions2 = {}
for var in productions:
    productions2[var] = set()

for var in productions.keys():
    setnou = set()
    for elem in productions[var]:
        if prodValida(elem):
            setnou.add(elem)
    productions2[var] = setnou

productions = productions2

print(productions)
#print(nonTerminals)

















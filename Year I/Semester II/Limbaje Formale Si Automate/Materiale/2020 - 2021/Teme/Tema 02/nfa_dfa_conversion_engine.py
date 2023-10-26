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
                            if sigma == True and letter not in alphabet and letter != chr(949):
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
            elif edge[1] not in alphabet and edge[1] != chr(949):
                return 0
        return 1
    else:
        return 0



class NFA:
    def __init__(self):
        self.num_states = 0
        self.states = []
        self.symbols = []
        self.num_accepting_states = 0
        self.accepting_states = []
        self.start_state = 0
        self.transition_functions = []

    def init_states(self):
        self.states = list(range(self.num_states))

    def print_nfa(self):
        print(self.num_states)
        print(self.states)
        print(self.symbols)
        print(self.num_accepting_states)
        print(self.accepting_states)
        print(self.start_state)
        print(self.transition_functions)

    def construct_nfa(self):
        self.num_states = len(nodes)
        self.init_states()
        self.symbols = alphabet
        self.num_accepting_states = len(final_nodes)
        self.accepting_states = final_nodes
        self.start_state = start
        self.transition_functions = transition


class DFA:
    def __init__(self):
        self.num_states = 0
        self.symbols = []
        self.num_accepting_states = 0
        self.accepting_states = []
        self.start_state = 0
        self.transition_functions = []
        self.q = []

    def convert_from_nfa(self, nfa):
        self.symbols = nfa.symbols
        self.start_state = nfa.start_state

        nfa_transition_dict = {}
        dfa_transition_dict = {}

        # Combine NFA transitions
        for transition in nfa.transition_functions:
            starting_state = transition[0]
            transition_symbol = transition[1]
            ending_state = transition[2]

            if (starting_state, transition_symbol) in nfa_transition_dict:
                nfa_transition_dict[(starting_state, transition_symbol)].append(ending_state)
            else:
                nfa_transition_dict[(starting_state, transition_symbol)] = [ending_state]

        self.q.append((0,))

        # Convert NFA transitions to DFA transitions
        for dfa_state in self.q:
            for symbol in nfa.symbols:
                if len(dfa_state) == 1 and (dfa_state[0], symbol) in nfa_transition_dict:
                    dfa_transition_dict[(dfa_state, symbol)] = nfa_transition_dict[(dfa_state[0], symbol)]

                    if tuple(dfa_transition_dict[(dfa_state, symbol)]) not in self.q:
                        self.q.append(tuple(dfa_transition_dict[(dfa_state, symbol)]))
                else:
                    destinations = []
                    final_destination = []

                    for nfa_state in dfa_state:
                        if (nfa_state, symbol) in nfa_transition_dict and nfa_transition_dict[(nfa_state, symbol)] not in destinations:
                            destinations.append(nfa_transition_dict[(nfa_state, symbol)])

                    if not destinations:
                        final_destination.append(None)
                    else:
                        for destination in destinations:
                            for value in destination:
                                if value not in final_destination:
                                    final_destination.append(value)

                    dfa_transition_dict[(dfa_state, symbol)] = final_destination

                    if tuple(final_destination) not in self.q:
                        self.q.append(tuple(final_destination))

        # Convert NFA states to DFA states
        for key in dfa_transition_dict:
            self.transition_functions.append(
                (self.q.index(tuple(key[0])), key[1], self.q.index(tuple(dfa_transition_dict[key]))))

        for q_state in self.q:
            for nfa_accepting_state in nfa.accepting_states:
                if nfa_accepting_state in q_state:
                    self.accepting_states.append(self.q.index(q_state))
                    self.num_accepting_states += 1

    def print_dfa(self):
        print(len(self.q))
        print("Sigma:")
        for x in self.symbols:
            print(x)
        print("Final nodes:")
        print(self.accepting_states)
        #print(str(self.num_accepting_states) + " " + " ".join(str(accepting_state) for accepting_state in self.accepting_states))
        print("Start state:")
        print(self.start_state)
        print("Transitions:")
        for transition in sorted(self.transition_functions):
            print(" ".join(str(value) for value in transition))

file = input()

if validate_input_file(file):
    '''print(start)
    print(nodes)
    print(transition)
    print(final_nodes)
    print(alphabet)'''

    nfa = NFA()
    nfa.construct_nfa()
    #print(len(nodes))
    #print(nfa.print_nfa())

    dfa = DFA()
    
    dfa.convert_from_nfa(nfa)
    dfa.print_dfa()
import sys
import numpy as np
import pdb


def select_random_path(E):
    # pentru linia 0 alegem primul pixel in mod aleator
    line = 0
    col = np.random.randint(low=0, high=E.shape[1], size=1)[0]
    path = [(line, col)]
    for i in range(E.shape[0]):
        # alege urmatorul pixel pe baza vecinilor
        line = i
        # coloana depinde de coloana pixelului anterior
        if path[-1][1] == 0:  # pixelul este localizat la marginea din stanga
            opt = np.random.randint(low=0, high=2, size=1)[0]
        elif path[-1][1] == E.shape[1] - 1:  # pixelul este la marginea din dreapta
            opt = np.random.randint(low=-1, high=1, size=1)[0]
        else:
            opt = np.random.randint(low=-1, high=2, size=1)[0]
        col = path[-1][1] + opt
        path.append((line, col))

    return path

def select_dynamic_programming_path(E):
    #TODO: scrieti codul
    return None


def select_path(E, method):
    if method == 'aleator':
        return select_random_path(E)
    elif method == 'programareDinamica':
        return select_dynamic_programming_path(E)
    else:
        print('The selected method %s is invalid.' % method)
        sys.exit(-1)
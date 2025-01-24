import sys
import numpy as np


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
    M = np.zeros(E.shape)
    M[0, :] = E[0, :]
    for i in range(1, M.shape[0]):
        for j in range(0, M.shape[1]):
            if j == 0:
                M[i, j] = E[i, j] + min(M[i - 1, j], M[i - 1, j + 1])
            elif j == M.shape[1] - 1:
                M[i, j] = E[i, j] + min(M[i - 1, j], M[i - 1, j - 1])
            else:
                M[i, j] = E[i, j] + min(M[i - 1, j], M[i - 1, j + 1], M[i - 1, j - 1])

    line = M.shape[0] - 1
    col = np.argmin(M[line, :])
    path = [0 for i in range(line + 1)]
    path[line] = (line, col)

    for line in range(M.shape[0] - 2, -1, -1):
        if col == 0:
            if M[line, col] > M[line, col + 1]:
                new_col = col + 1
            else:
                new_col = col
        elif col == M.shape[1] - 1:
            if M[line, col] > M[line, col - 1]:
                new_col = col - 1
            else:
                new_col = col
        else:
            if M[line, col] <= M[line, col + 1] and M[line, col] <= M[line, col - 1]:
                new_col = col
            elif (
                M[line, col + 1] <= M[line, col]
                and M[line, col + 1] <= M[line, col - 1]
            ):
                new_col = col + 1
            elif (
                M[line, col - 1] <= M[line, col]
                and M[line, col - 1] <= M[line, col + 1]
            ):
                new_col = col - 1
        path[line] = (line, new_col)
        col = new_col

    return path


def select_path(E, method):
    if method == "aleator":
        return select_random_path(E)
    elif method == "programareDinamica":
        return select_dynamic_programming_path(E)
    else:
        print("The selected method %s is invalid." % method)
        sys.exit(-1)

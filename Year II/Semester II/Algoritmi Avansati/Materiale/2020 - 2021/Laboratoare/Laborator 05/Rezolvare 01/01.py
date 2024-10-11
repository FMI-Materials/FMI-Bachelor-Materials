import numpy as np
from util import *


def compute_turn(p, q, r):
    delta = np.array([[1, 1, 1], [p[0], q[0], r[0]], [p[1], q[1], r[1]]])
    det = np.linalg.det(delta)
    return det


if __name__ == '__main__':
    p1 = read_point("p")
    p2 = read_point("q")
    p3 = read_point("r")
    turn = compute_turn(p1, p2, p3)
    if turn == 0:
        print("\n puncte coliniare")
    elif turn<0:
        print("\n viraj la dreapta")
    else:
        print("\n viraj la stanga")

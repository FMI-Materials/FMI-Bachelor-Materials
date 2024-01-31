import sys

from geometry import *
from util import *


def get_intersection(halfplanes: list[HalfPlane]):
    x_min, x_max = -sys.maxsize, sys.maxsize
    y_min, y_max = -sys.maxsize, sys.maxsize
    for hp in halfplanes:
        current_min, current_max = -sys.maxsize, sys.maxsize

        if hp.a > 0:
            current_max = -hp.b / hp.a
        else:
            current_min = -hp.b / hp.a

        if hp.vertical:
            y_min = max(y_min, current_min)
            y_max = min(y_max, current_max)
        else:
            x_min = max(x_min, current_min)
            x_max = min(x_max, current_max)
    if x_min > x_max or y_min > y_max:
        return 0
    if min(x_min, y_min) == -sys.maxsize or max(x_max, y_max) == sys.maxsize:
        return 2
    return 1


def read():
    n = input_int("n = ")
    halfplanes = list()
    for i in range(n):
        halfplanes.append(HalfPlane.read(f"H{i + 1}"))
    return halfplanes


if __name__ == '__main__':
    # halfplanes = read()

    # halfplanes = [HalfPlane(1, 0, -1), HalfPlane(-1, 0, 2), HalfPlane(0, 1, 3)]
    # halfplanes = [HalfPlane(-1, 0, 1), HalfPlane(1, 0, -2), HalfPlane(0, 1, 3)]
    halfplanes = [HalfPlane(-1, 0, 1), HalfPlane(1, 0, -2), HalfPlane(0, 1, 3), HalfPlane(0, -2, -8)]

    intersection = get_intersection(halfplanes)
    if intersection == 0:
        print("Intersecția este vidă")
    elif intersection == 1:
        print("Intersecția este nevidă, mărginită")
    else:
        print("Intersecția este nevidă, nemărginită")

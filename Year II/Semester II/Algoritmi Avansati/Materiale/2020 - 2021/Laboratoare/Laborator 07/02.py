import sys

from geometry import Point, HalfPlane
from util import *


def read():
    q = Point.read("Q")
    n = input_int("n = ")
    halfplanes = list()
    for i in range(n):
        halfplanes.append(HalfPlane.read(f"H{i + 1}"))
    return q, halfplanes


def get_rectangle_area(halfplanes: list[HalfPlane], q: Point):
    x_min, x_max = -sys.maxsize, sys.maxsize
    y_min, y_max = -sys.maxsize, sys.maxsize

    for hp in halfplanes:
        if not hp.contains_point(q):
            continue
        l = hp.get_line()
        if hp.vertical:
            if l < q.y:
                y_min = max(y_min, l)
            if l > q.y:
                y_max = min(y_max, l)
        else:
            if l < q.x:
                x_min = max(x_min, l)
            if l > q.x:
                x_max = min(x_max, l)

    if min(x_min, y_min) == -sys.maxsize or max(x_max, y_max) == sys.maxsize:
        return -1
    return (x_max - x_min) * (y_max - y_min)


if __name__ == '__main__':
    # q, halfplanes = read()
    # q, halfplanes = Point(1.5, -4), [HalfPlane(-1, 0, 1), HalfPlane(1, 0, -2), HalfPlane(0, 1, 3)]
    # q, halfplanes = Point(0, 0), [HalfPlane(-1, 0, 1), HalfPlane(1, 0, -2), HalfPlane(0, 1, 3), HalfPlane(0, -2, -8)]
    # q, halfplanes = Point(1.25, -3.5), [HalfPlane(-1, 0, 1), HalfPlane(1, 0, -2), HalfPlane(0, 1, 3), HalfPlane(0, -2, -8)]
    q, halfplanes = Point(2, 1), [HalfPlane(-1, 0, 1), HalfPlane(0, -3, -6), HalfPlane(0, 2, -6), HalfPlane(1, 0, -3), HalfPlane(0, 1, -2), HalfPlane(2, 0, -10), HalfPlane(0, -1, -3), HalfPlane(-4, 0, 0), HalfPlane(-1, 0, 1), HalfPlane(0, -1, -1), HalfPlane(1, 0, -4)]

    area = get_rectangle_area(halfplanes, q)
    if area == -1:
        print("(a) Nu există un dreptunghi cu proprietatea cerută")
    else:
        print(f"(b) Valoarea minimă a ariilor dreptunghiurilor cu proprietatea cerută este {area}")

from util import *
from ex1 import *
from ex2 import *


def bin_search(points, point):
    l = 0
    r = len(points) - 1
    while l <= r:
        m = (l + r) // 2
        turn = compute_turn(points[0], points[m], point)
        if turn > 0:
            l = m + 1
        elif turn < 0:
            r = m - 1
        else:
            return m
    return r


def relative_pos(points, point):
    i = bin_search(points, point)
    if i == 0 or i == len(points) - 1:
        return -1

    if compute_turn(points[i - 1], points[i], point) == 0:
        return 0

    turn = compute_turn(points[i], point[i + 1], point)
    if turn > 0:
        return 1
    elif turn < 0:
        return -1
    return 0


if __name__ == '__main__':
    points = read_points()

    point = read_point("punct relativ:")
    pos = relative_pos(points, point)

    if pos == 1:
        print("punctul este in interior")
    elif pos == 0:
        print("punctul este pe laturi")
    elif pos == -1:
        print("punctul este in exterior")

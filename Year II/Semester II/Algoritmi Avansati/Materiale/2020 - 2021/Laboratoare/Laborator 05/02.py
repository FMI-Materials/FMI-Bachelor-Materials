from util import *
from ex1 import *


def graham_scan_inferior(p):
    l = [p[0], p[1]]
    for i in range(2, len(p)):
        l.append(p[i])
        while len(l) > 2 and compute_turn(l[-3], l[-2], l[-1]) < 0:
            l.pop(-2)
    return l


def graham_scan_superior(p):
    l = [p[0], p[1]]
    for i in range(2, len(p)):
        l.append(p[i])
        while len(l) > 2 and compute_turn(l[-3], l[-2], l[-1]) > 0:
            l.pop(-2)
    return l


def graham_scan(p):
    p.sort(key=lambda point: point[0])
    p.sort(key=lambda point: point[1])
    inferior = graham_scan_inferior(p)

    p.sort(key=lambda point: point[0])
    p.sort(key=lambda point: point[1])
    superior = graham_scan_superior(p)

    for pp in superior:
        if pp not in inferior:
            inferior.append(pp)
    return inferior


def jarvis_march(p):
    a = min(p, key=lambda point: point[0])
    index = p.index(a)
    l = index
    result = [a]
    while True:
        q = (l + 1) % len(p)
        for i in range(len(p)):
            if i == l:
                continue
            d = compute_turn(p[l], p[i], p[q])
            if d < 0:
                q = i
        l = q
        if l == index:
            break
        result.append(p[q])

    return result


if __name__ == '__main__':
    # points = read_points()
    # points = [(-8, 0), (-6, -2), (-4, 0), (-4, 2), (-3, 2), (-2, 2), (0, -1), (2, -4)]
    # points = [(1, 1), (2.9, 0.5), (2.8, 1), (2.6, 1.4), (2.2, 1.8), (2, 2.5), (3.5, 3), (4, 2), (5, 1)]
    # points = [(-2, 4), (-1, 1), (0, 1), (2, 1), (4, 3), (5, 5), (6, 9), (8, 4), (10, 6)]
    for a in range(-100, -2):
        points = [(0, 0), (3, 0), (0, 2), (a, 2), (-2, 1), (-2, 4)]
        # print(graham_scan(points))
        l = len(jarvis_march(points))
        print(l)

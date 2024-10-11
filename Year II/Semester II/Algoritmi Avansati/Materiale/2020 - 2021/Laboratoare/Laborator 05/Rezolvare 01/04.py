from ex1 import *
from math import sqrt
import sys


def convex_hull(points):
    def get_envelope():
        v = []
        for p in points:
            while len(v) >= 2 and compute_turn(v[-2], v[-1], p) <= 0:
                v.pop(-1)
            v.append(p)
        v.pop(-1)
        return v

    points.sort()
    v1 = get_envelope()

    points.reverse()
    v2 = get_envelope()

    v1.extend(v2)
    return v1


def calculate_distance(p1, p2=None):
    if p2 is None:
        p2 = (0, 0)
    return sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2))


def compute_tsp(points):
    points_left = set()
    act = convex_hull(points)

    for p in points:
        points_left.add(p)
    for p in act:
        points_left.remove(p)

    def distance1(point, pos):
        ans = calculate_distance(act[pos], point) + calculate_distance(point, act[(pos + 1) % len(act)])
        ans /= calculate_distance(act[pos], act[(pos + 1) % len(act)])
        return ans

    def distance2(point, pos):
        ans = calculate_distance(act[pos], point) + calculate_distance(point, act[(pos + 1) % len(act)])
        ans -= calculate_distance(act[pos], act[(pos + 1) % len(act)])
        return ans

    while len(points_left) > 0:
        best = [sys.maxsize, None, None]

        for p in points_left:
            id = 0
            best_dist = sys.maxsize

            for pos in range(len(act)):
                d_act = distance1(p, pos)
                if d_act < best_dist:
                    best_dist = d_act
                    id = pos

            rap_act = distance2(p, id)
            if rap_act < best[0]:
                best[0] = rap_act
                best[1] = p
                best[2] = id

        points_left.remove(best[1])
        act.insert(best[2], best[1])
    return act


if __name__ == '__main__':
    points = read_points()
    resp = compute_tsp(points)

    for p in resp:
        print(f"({p[0]}, {p[1]})")
    print(f"({resp[0][0]}, {resp[0][1]})")

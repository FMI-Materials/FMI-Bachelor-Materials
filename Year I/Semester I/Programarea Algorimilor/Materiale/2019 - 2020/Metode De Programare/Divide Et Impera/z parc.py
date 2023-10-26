m = [
    [0] * 4,
    [0] * 4,
    [0] * 4,
    [0] * 4
]
k = 1
def zPath(p1, p2):
    global k
    # print(p1,p2)
    if (p1[0] > p2[0] or p1[1] > p2[1]):
        return None
    if (abs(p1[0] - p2[0]) == 0 or abs(p1[1] - p2[1]) == 0):
        m[p1[0]][p1[1]] = k
        k += 1
    else:
        mx, my = (p1[0] + p2[0]) // 2, (p1[1] + p2[1]) // 2
        zPath((p1[0], p1[1]), (mx, my))
        zPath((mx + 1, p1[1]), (p2[0], my))
        zPath((p1[0], my + 1), (mx, p2[1]))
        zPath((mx + 1, my + 1), (p2[0], p2[1]))


zPath((0, 0), (3, 3))

print("\n".join(map(str, m)))
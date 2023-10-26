import math

f = open("retea2.in")
line = f.readline()
v = line.split()
N = int(v[0])
M = int(v[1])
blocuri = []
centrale = []


def dist_euclidiana(e1, e2):
    x1 = e1[0]
    y1 = e1[1]
    x2 = e2[0]
    y2 = e2[1]
    dist = math.sqrt( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
    return dist

for i in range(N):
    line = f.readline()
    v = line.split()
    x = int(v[0])
    y = int(v[1])
    centrale.append((x,y))

for i in range(M):
    line = f.readline()
    v = line.split()
    x = int(v[0])
    y = int(v[1])
    blocuri.append((x,y))



# best = [-1] * (M)
# lista = []
# for i in range(N):
#     for j in range(M):
#         val = dist_euclidiana(centrale[i], blocuri[j])
#         if val < best[j] or best[j] == -1:
#             best[j] = val
#
# sel = [0] * (M)
# sol = 0
# for j in range(M):
#     indice = -1
#     for i in range(M):
#         if sel[i]:
#             continue
#         if indice == -1:
#             continue
#         if best[indice] > best[i]:
#             indice = i
#     sol = sol + math.sqrt(best[indice])
#     sel[indice] = 1
#     for i in range(M):
#         if sel[i]:
#             continue
#         val = dist_euclidiana(blocuri[indice], blocuri[i])
#         best[i] = min(best[i], val)
#
# print(sol)
# print(best)
#
#
#



f.close()
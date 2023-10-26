def readList():
    n = int(input())
    L = [int(x) for x in input().split()]
    return n, L


def findPos(L, x, i, j):
    for k in range(i, j + 1):
        if L[k] > x:
            return k
    return -1


n, L = readList()
for i in range(n):
    if findPos(L, L[i], i + 1, n - 1) != -1:
        print("Nu")
        break
if i == n - 1:
    print("Da")

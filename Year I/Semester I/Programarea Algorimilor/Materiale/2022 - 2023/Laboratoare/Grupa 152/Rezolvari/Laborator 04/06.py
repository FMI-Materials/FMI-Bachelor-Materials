def cautare(x, L, cmpValori):
    for i in range(len(L) - 1, -1, -1):
        if cmpValori(x, L[i]):
            return i
    return None


def cmpValori(x, y):
    return x == y


def isPalindrom(L):
    n = len(L)
    for i in range(n // 2):
        k = cautare(L[i], L, cmpValori)
        if i != n - k - 1:
            return False
    return True


L = [int(x) for x in input().split()]
print(isPalindrom(L))
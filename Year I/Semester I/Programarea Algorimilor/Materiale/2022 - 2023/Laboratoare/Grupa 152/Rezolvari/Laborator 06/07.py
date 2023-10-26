def is_palindrom(L):
    return "DA" if L == L[::-1] else "NU"


L = [int(x) for x in input().split()]
print(is_palindrom(L))

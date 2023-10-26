n = int(input())
def palindrom(n):
    m = 0
    aux = n
    while aux > 0:
        m = m * 10 + aux % 10
        aux //= 10
    return m == n
print(palindrom(n))
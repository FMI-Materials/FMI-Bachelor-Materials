def ex6(n):
    def gcd(a, b):
        if b == 0:
            return a
        return gcd(b, a % b)
    return [[1 if gcd(i + 1, j + 1) == 1 else 0 for j in range(n)] for i in range(n)]


n = int(input())
print(ex6(n))

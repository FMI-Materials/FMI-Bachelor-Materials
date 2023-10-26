def ex12(n):
    def a(n):
        if n <= 0:
            return 0
        return a(n - 1) + 1 / n

    def b(n):
        if n <= 1:
            return 1
        return b(n - 2) + b(n - 1)

    def c(n):
        if n <= 0:
            return 0
        return c(n - 1) + (-1) ** n * n

    def S(f, n):
        if n <= 0:
            return 0
        return f(n) + S(f, n - 1)

    return S(a, n), S(b, n), S(c, n)


print(ex12(9))

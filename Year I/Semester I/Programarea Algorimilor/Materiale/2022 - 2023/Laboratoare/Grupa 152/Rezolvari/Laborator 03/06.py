L = [1, 2, 3, 4]
print([(L[x], L[x + 1]) for x in range(len(L) - 1)])

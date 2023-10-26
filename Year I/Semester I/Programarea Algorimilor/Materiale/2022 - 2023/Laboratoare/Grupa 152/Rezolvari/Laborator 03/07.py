n = int(input())
L = [[f"{x} * {y} = {x * y}" for y in range(1, n + 1)] for x in range(1, n + 1)]
print(L)

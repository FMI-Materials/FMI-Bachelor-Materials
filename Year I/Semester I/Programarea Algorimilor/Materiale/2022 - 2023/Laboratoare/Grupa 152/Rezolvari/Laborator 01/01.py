x, y = map(int, input().split())
x ^= y
y = x ^ y
x ^= y
print(x, y)

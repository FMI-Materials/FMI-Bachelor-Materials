L = input().split()

d1 = {x: L.count(x) for x in L}
d2 = {x: [y[0] for y in d1.items() if y[1] == x] for x in d1.values()}

print(d1)
print(d2)

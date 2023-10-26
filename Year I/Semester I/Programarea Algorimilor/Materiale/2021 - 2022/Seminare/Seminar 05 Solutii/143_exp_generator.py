"""
print(range(10))

t=(int(x) for x in input().split()) #generator
print(sum(t))
print(sum(t))

t=[int(x) for x in input().split()]
print(sum(t))
print(sum(t))
"""

def gen_patrate_pana_la(n):
    for k in range(n):
        yield k ** 2

for x in gen_patrate_pana_la(10):
    print(x, end=" ")
print("\nsuma:")

t=gen_patrate_pana_la(10)
print(sum(t))
print(sum(t))

t=gen_patrate_pana_la(10)
print(next(t))
print(next(t))
print(list(t))


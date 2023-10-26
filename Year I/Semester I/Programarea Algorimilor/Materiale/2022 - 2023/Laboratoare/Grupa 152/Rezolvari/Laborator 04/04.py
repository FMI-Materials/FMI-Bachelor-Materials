import functions_04 as f

n, v = f.citire()
f.semn(v)
for i in f.valpoz(v):
    if i > 0:
        print(f"-{i}", end=" ")
f.semn(v)
print('\n', end="")
for i in f.valpoz(v):
    if i > 0:
        print(i, end=" ")

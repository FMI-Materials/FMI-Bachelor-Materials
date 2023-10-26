n = int(input())
for mask in range(1 << n):
    s = ""
    for i in range(n):
        if mask & (1 << i):
            s += str(i + 1) + " "
    print(s)
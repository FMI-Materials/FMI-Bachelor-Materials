# Problem: Given n and a list of distinct n-2 numbers x, where x<=n.
# Find the missing 2 numbers using xor

def find_nums(seq, n):
    xor = 0
    for e in seq:
        xor ^= e
    for e in range(1, n + 1):
        xor ^= e
    rb = xor & ~(xor - 1)
    x = y = 0
    for e in seq:
        if e & rb:
            x ^= e
        else:
            y ^= e
    for e in range(1, n + 1):
        if e & rb:
            x ^= e
        else:
            y ^= e
    return {x, y}


print(find_nums([1, 2, 4, 6], 6))



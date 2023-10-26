# Tuplu
# Set
# Dictionar
# Lista
'''
# 8
s1 = "test"
s2 = "lucru"
print(s1[0:len(s1)//2]+s2+s1[len(s1)//2:])

# 6
# [1,2,3,4]
# abc: 3
# vve: 6
d = dict()
list = [11, 45, 8, 11, 23, 45, 23, 45, 89]
for x in list:
    d[x] = list.count(x)
print(d)

# 7
aTuple = ("Orange", [10, 20, 30], (5, 15, 25))
print(aTuple[1][1])

def find_nums(seq, n):
    xor = 0
    for e in seq:
        xor ^= e
    for e in range(1, n + 1):
        xor ^= e
    rb = xor & ~(xor - 1)
    # a ^ b = 101
    # [1,2,3,5] 6
    #
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

# 001
# 010
# 011
# 100
# 101
# 110
# 1 0 = 1
# 0 1 = 1
# 0 0 = 0
# 1 1 = 0

def find_num(list, n):
    acc1 = acc2 = 0
    for x in range(1, n+1):
        acc1 ^= x
    for x in list:
        acc2 ^= x
    return acc1 ^ acc2


print(find_num([1,2,4,5,6], 6))

import random
# Lista <100
# Sortati lista eficient cu vectori de frecv
L = [0 for x in range(101)]
lis = [random.randint(1, 100) for x in range(1, 100)]
for x in lis:
    L[x] += 1
ind = 0
for x in L:
    while x > 0:
        print(ind, end=" ")
        x -= 1
    ind += 1
print()
'''
# 12
a = "1a12B4C"
b = ""
num = ""
for i in range(len(a)):
    if a[i].isnumeric():
        num += a[i]
    else:
        num_int = int(num)
        while num_int > 0:
            b += a[i]
            num_int -= 1
        num = ""
print(b)



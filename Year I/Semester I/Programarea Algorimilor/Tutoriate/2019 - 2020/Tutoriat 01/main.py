# 1
'''
n = int(input())
list = []
for i in range(n):
    x = int(input())
    list.append(x)
min1 = min2 = min3 = 99999
for l in list:
    if l < min1:
        min3 = min2
        min2 = min1
        min1 = l
    elif l < min2:
        min3 = min2
        min2 = l
    elif l < min3:
        min3 = l
print(min1, min2, min3)
'''
# 2
'''
word1 = input()
word2 = input()
def is_anagram(x, y):
    if len(x) != len(y):
        return False
    used = dict()
    for l in x:
        if l in used:
            used[l] += 1
        else:
            used[l] = 1
    # abcc ccbb
    # a 1
    # b -1
    # c 0
    for l in y:
        if l in used:
            used[l] -= 1
            if used[l] < 0:
                return False
        else:
            return False
    return True
print(is_anagram(word1, word2))
# 3
'''
# A = {x | x<- B, x<2}
'''
l = [x if x < 2 else 7 for x in range(10) if x%2==0]
# 0 1 2 3 ... 10
list2 = ["haha", "poc", "Poc", "haha", "POC", "haHA", "hei", "hey", "HahA", "poc", "Hei"]
usages = dict()
for l in list2:
    if l.lower() in usages:
        usages[l.lower()] += 1
    else:
        usages[l.lower()] = 1
for u in usages:
    print(u, usages[u])
'''
# 3
# 0 1 2
# 1 2 3
# 2 3 4
'''
n = 4
mat = [[0 for y in range(n)] for x in range(n)]
l = [1,2,3,4,5]
print(l[-3:-1])
'''
#    0 1 2 3 4
#   -5 -4 -3 -2 -1
# min
'''
nr = int(input("n = "))
li = [int(input()) for x in range(nr)]
def maxi(l):
    mx = 0
    for x in l:
        if x > mx:
            mx = x
    return mx
print("maximul este =", maxi(li))
'''
# Bubble sort
# 2,4,1,4,2,9,57
# 1 2 2 4 4 9 57
l = [2,4,57,1,4,9,2]
n = len(l)
for i in range(n-1):
    for j in range(n-i-1):
        if l[j] > l[j+1]:
            l[j], l[j+1] = l[j+1], l[j]
print(l)
# Xor function
# se citesc n-2 numere
l = [1, 2, 3, 4, 5, 7, 9]
x = 0
for y in l:
    x ^= y
print(x-9)





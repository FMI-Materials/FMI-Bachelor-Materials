# 1
def anagram(a, b):
    if len(a) != len(b):
        return False
    usages = dict()
    for x in a:
        if x in usages:
            usages[x] += 1
        else:
            usages[x] = 1
    for x in b:
        if x in usages and usages[x]>0:
            usages[x] -= 1
        else:
            return False
    return True


print("Este anagrama:", anagram("abc", "cba"))

# 2
def anagram_changes(a, b):
    changes = 0
    usages = dict()
    for x in a:
        if x in usages:
            usages[x] += 1
        else:
            usages[x] = 1
    for x in b:
        if x in usages and usages[x] > 0:
            usages[x] -= 1
        else:
            changes += 1
    return changes

print("Modificari anagrama:", anagram_changes("abc", "cba"))

# 5
def factorial(n):
    if n == 1:
        return 1
    return n*factorial(n-1)

print("Factorial:", factorial(3))

# 6
def fibonacci(n):
    if n == 0 or n==1:
        return n
    return fibonacci(n-1)+fibonacci(n-2)

print("Fibonacci:", fibonacci(10))

# 7
def maxim(list):
    if len(list) == 0:
        return 0
    return max(list[0], maxim(list[1:]))

print("Maxim:", maxim([1,2,3,4,5,6,99,1,101,2]))

# 7b
def minim(list):
    if len(list) == 0:
        return 0
    return min(list[0], minim(list[1:]))


# 8
def atoi(string, num = 0):
    if len(string) == 1:
        return int(string) + (num * 10)
    num = int(string[0]) + (num * 10)
    return atoi(string[1:], num)


print(atoi("112"))

# 9
def first(x):
    if x < 10:
        return x
    return first(x//10)

print("Prima cifra este:", first(21342134213))

#10
def b_search(list, x, l, r):
    if l > r:
        return False
    m = (l+r)//2
    if x == list[m]:
        return True
    if x < list[m]:
        return b_search(list, x, l, m-1)
    return b_search(list, x, m+1, r)

print(b_search([1,2,3,4,5,6], 3, 0, 5))

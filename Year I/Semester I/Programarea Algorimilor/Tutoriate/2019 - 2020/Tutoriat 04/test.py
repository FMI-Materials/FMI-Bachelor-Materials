
# 1
# abc bca
def anagram(a, b):
    freq = [0 for _ in range(26)]
    for x in a:
        freq[ord(x)-ord('a')] += 1
    for x in b:
        freq[ord(x)-ord('a')] -= 1
        if freq[ord(x)-ord('a')] < 0:
            return False
    return True

print(anagram("abc", "cba"))

# 2
def changes_anagram(a, b):
    changes = 0
    freq = [0 for _ in range(26)]
    for x in a:
        freq[ord(x)-ord('a')] += 1
    for x in b:
        freq[ord(x)-ord('a')] -= 1
        if freq[ord(x)-ord('a')] < 0:
            changes += 1
            freq[ord(x) - ord('a')] = 0
    return changes

print(changes_anagram("abcc", "abcd"))

# 0 -> 1
# 1 -> 1
# 5 = 5*(4*3*2*1)
def factorial(n):
    if n == 1:
        return 1
    return n*factorial(n-1)

print(factorial(3))

# 0 1 1 2 3 5 8
def fibonacci(n):
    if n == 0:
        return 0
    if n <= 2:
        return 1
    return fibonacci(n-1)+fibonacci(n-2)

print(fibonacci(8))

def maxim(l):
    if len(l) == 1:
        return l[0]
    return max(l[0], maxim(l[1:]))

print(maxim([1,2,3,4,101,22,1]))


def atoi(string, num = 0):
    if len(string) == 1:
        return int(string) + (num * 10)
    num = int(string[0]) + (num * 10)
    return atoi(string[1:], num)

print(atoi("112"))

def b_search(list, x, l, r):
    if l > r:
        return False
    mij = (l + r) // 2
    if x == list[mij]:
        return True
    if x > list[mij]:
        return b_search(list, x, mij + 1, r)
    return b_search(list, x, l, mij - 1)

# 1 2 3 4 5 6
# l: 3
# r: 3

print(b_search([1,2,3,4,5,6], 8,0,5))



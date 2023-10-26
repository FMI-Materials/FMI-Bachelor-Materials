# 1
color = ['Red', 'Green', 'White', 'Black', 'Pink', 'Yellow']
try:
    with open('abc.txt', "w") as myfile:
        for c in color:
            myfile.write(c+" ")
except:
    print("Cannot open file")

content = open('abc.txt')
print(content.read())
content.close()

# 2
color = ['Red', 'Green', 'White', 'Black', 'Pink', 'Yellow']

d = dict()
with open('abc.txt', "r") as myfile:
    line = myfile.read()
    for char in line:
        if char in d:
            d[char] += 1
        else:
            d[char] = 1

print(d)

# 3
color = ['Red', 'Green', 'White', 'Black', 'Pink', 'Yellow']

d = {}
with open('abc.txt', "r") as myfile:
    line = myfile.read()
    cuvinte = line.split(" ")
    for cuvant in cuvinte:
        if cuvant in d:
            d[cuvant] += 1
        else:
            d[cuvant] = 1

print(d)

# 4
litere = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
          'w', 'x', 'y', 'z']

for lit in litere:
    with open(lit + ".txt", "w") as f:
        f.write(lit)

# 5
with open("abc.txt", "r") as f:
    lmax = 0
    cuvmax = ""
    line = f.readline()
    while line != "":
        cuvinte = line.split()
        for cuv in cuvinte:
            if len(cuv) > lmax:
                lmax = len(cuv)
                cuvmax = cuv
        line = f.readline()

print(cuvmax)


# 6
def aux(a, b):
    return a + b


def f(a, b, aux):
    return aux(a, b)


print(f(2, 3, aux))

# 7
def concat(*args):
    r = ""
    for c in args:
        r += c
    return r


print(concat("a", "s", "d"))


# 8

def lis(*args):
    li = []

    for i in args:
        li.append(i)

    li.sort(reverse=True)

    return li


print(lis(1, 2, 10, -3, 9, 8, 3, 150, 2))


# 9
def string_reverse(str1):
    rstr1 = ''
    index = len(str1)
    while index > 0:
        rstr1 += str1[index - 1]
        index = index - 1
    return rstr1


print(string_reverse('1234abcd'))


# 10
def pr(x):
    print(x)


# 11
def perfect_number(n):
    sum = 0
    for x in range(1, n):
        if n % x == 0:
            sum += x
    return sum == n


print(perfect_number(6))

# 12
import string, sys


def ispangram(str1, alphabet=string.ascii_lowercase):
    alphaset = set(alphabet)
    return alphaset <= set(str1.lower())


print(ispangram('The quick brown fox jumps over the lazy dog'))


# 13

# Returns the rotated list
def rightRotate(lists, num):
    output_list = []

    # Will add values from n to the new list
    for item in range(len(lists) - num, len(lists)):
        output_list.append(lists[item])

        # Will add the values before
    # n to the end of new list
    for item in range(0, len(lists) - num):
        output_list.append(lists[item])

    return output_list


# Driver Code
rotate_num = 3
list_1 = [1, 2, 3, 4, 5, 6]

print(rightRotate(list_1, rotate_num))

# 14 Function to convert decimal number
# to binary using recursion
def DecimalToBinary(num):
    if num > 1:
        DecimalToBinary(num // 2)
    print(num % 2, end='')


# Driver Code
if __name__ == '__main__':
    # decimal value
    dec_val = 24

    # Calling function
    DecimalToBinary(dec_val)
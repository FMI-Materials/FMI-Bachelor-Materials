# concise definition of the Luhn checksum:
#
# "For a card with an even number of digits, double every odd numbered
# digit and subtract 9 if the product is greater than 9. Add up all
# the even digits as well as the doubled-odd digits, and the result
# must be a multiple of 10 or it's not a valid card. If the card has
# an odd number of digits, perform the same addition doubling the even
# numbered digits instead."
#
# Implement the Luhn Checksum algorithm as described above.

# is_luhn_valid takes a credit card number as input and verifies
# whether it is valid or not. If it is valid, it returns True,
# otherwise it returns False.

import random


def luhn_digit(n):
    n = 2 * n
    if n > 9:
        return n - 9
    else:
        return n


def luhn_checksum(n):
    l = len(n)
    sum = 0
    if l % 2 == 0:
        for i in range(l):
            if (i+1) % 2 == 0:
                sum += int(n[i])
            else:
                sum += luhn_digit(int(n[i]))
    else:
        for i in range(l):
            if (i+1) % 2 == 0:
                sum += luhn_digit(int(n[i]))
            else:
                sum += int(n[i])
    return sum % 10


def is_luhn_valid(n):
    return luhn_checksum(n) == 0


def generate(pref,l):
    nrand = l - len(pref) - 1
    assert nrand > 0
    n = pref
    for i in range(nrand):
        n += str(random.randrange(10))
    n += "0"
    check = luhn_checksum(n)
    if check != 0:
        check = 10 - check
    n = n[:-1] + str(check)
    return n


def check(pref,l,num):
    if len(num) != l:
        return False
    preflen = len(pref)
    if num[:preflen] != pref:
        return False
    return is_luhn_valid(num)


# pref = "372542"
pref = "37"
print(generate(pref, 15))

for i in range(10000):
    n = generate(pref, 15)
    assert check(pref, 15, n)

N = 100000
valid = 0
for i in range(N):
    n = str(random.randint(0,1000000000000000)).zfill(15)
    if check(pref, 15, n):
        valid += 1
print(str(valid) + " valid out of " + str(N))

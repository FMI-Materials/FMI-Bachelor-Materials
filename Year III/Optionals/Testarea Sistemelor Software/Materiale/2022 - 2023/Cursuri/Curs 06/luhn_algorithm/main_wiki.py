import random


def luhn_checksum_wikipedia(card_number):
    def digits_of(n):
        return [int(d) for d in str(n)]
    digits = digits_of(card_number)
    odd_digits = digits[-1::-2]
    even_digits = digits[-2::-2]
    checksum = 0
    checksum += sum(odd_digits)
    for d in even_digits:
        checksum += sum(digits_of(d*2))
    return checksum % 10


def is_luhn_valid_wikipedia(card_number):
    return luhn_checksum_wikipedia(card_number) == 0


def generate(pref, l):
    nrand = l - len(pref) - 1
    assert nrand > 0
    n = pref
    for i in range(nrand):
        n += str(random.randrange(10))
    n += "0"
    check = luhn_checksum_wikipedia(n)
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
    return is_luhn_valid_wikipedia(n)


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

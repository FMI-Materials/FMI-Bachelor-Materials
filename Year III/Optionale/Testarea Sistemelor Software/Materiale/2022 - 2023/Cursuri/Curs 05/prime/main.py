# CORRECT SPECIFICATION:
#
# isPrime checks if a positive integer is prime.
#
# A positive integer is prime if it is greater than
# 1, and its only divisors are 1 and itself.
#
# TASKS:
#
# 1) Add an assertion to test() that shows
#    isPrime(number) to be incorrect for
#    some input.
#
# 2) Write isPrime2(number) to correctly
#    check if a positive integer is prime.

# Note that there is an error where isPrime() incorrectly returns False for an input of 2,
# despite 2 being a prime number.

# Quiz

# Add an assertion to test() that shows isPrime(number) to be incorrect for some input.
# Write isPrime2(number) to correctly check if a number is prime.


import math


def isPrime(number):
    if number == 2:
        return True
    if number <= 1 or (number % 2) == 0:
        return False
    for check in range(3, int(math.sqrt(number))):
        if (number % check) == 0:
            return False
    return True


def isPrime2(number):
    if number == 2:
        return True
    if number <= 1 or (number % 2) == 0:
        return False
    for check in range(3, int(math.sqrt(number)) + 1):
        if (number % check) == 0:
            return False
    return True


def check(n):
    print("isPrime(" + str(n) + ") = " + str(isPrime(n)))


def check2(n):
    print("isPrime2(" + str(n) + ") = " + str(isPrime2(n)))


check(1)
check(2)
check(3)
check(4)
check(5)
check(20)
check(21)
check(22)
check(23)
check(24)
check(6)
check(7)
check(8)
check(9)
check(10)
check(25)
check(26)
check(27)
check(28)
check(29)
check(6)
check2(7)
check2(8)
check2(9)
check2(10)
check2(25)
check2(26)
check2(27)
check2(28)
check2(29)


def test():
    assert isPrime(1) == False
    assert isPrime(2) == True
    assert isPrime(3) == True
    assert isPrime(4) == False
    assert isPrime(5) == True
    assert isPrime(20) == False
    assert isPrime(21) == False
    assert isPrime(22) == False
    assert isPrime(23) == True
    assert isPrime(24) == False

    assert isPrime(6) == False
    assert isPrime(7) == True
    assert isPrime(8) == False
    assert isPrime(9) == True
    assert isPrime(10) == False
    assert isPrime(25) == True
    assert isPrime(26) == False
    assert isPrime(27) == False
    assert isPrime(28) == False
    assert isPrime(29) == True


def test2():
    assert isPrime2(2) == True
    assert isPrime2(6) == False
    assert isPrime2(7) == True
    assert isPrime2(8) == False
    assert isPrime2(9) == False
    assert isPrime2(10) == False
    assert isPrime2(25) == False
    assert isPrime2(26) == False
    assert isPrime2(27) == False
    assert isPrime2(28) == False
    assert isPrime2(29) == True


test()
test2()

def ex11(L):
    def is_prime(n):
        for i in range(2, n):
            if n % i == 0:
                return False
        return True
    return [i for i in L if not is_prime(i)]


print(ex11([3, 2, 4, 6, 7, 12, 16]))

def ex9(n):
    def is_prime(n):
        for i in range(2, n):
            if n % i == 0:
                return False
        return True
    return [i for i in range(2, n) if is_prime(i)]


print(ex9(10))

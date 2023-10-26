def isPrime(n):
    if n == 2:
        return True
    elif n < 2 or not(n % 2):
        return False
    else:
        d = 3
        while d * d < n and n % d:
            d += 2
        return d * d > n
a, b = map(int, input().split())
for i in range(b, a, -1):
    if isPrime(i):
        print(i)
        break
else:
    print(f"Nu exista numere prime in intervalul [{a}, {b}]")
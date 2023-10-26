def genPrimes():
    yield 2
    x = 3
    while True:
        div = 3
        while div * div <= x and x % div:
            div += 2
        if div * div > x:
            yield x
        x += 2


n, c = input().split()
n = int(n)
count = 0
for x in genPrimes():
    print(x, end=" ")
    count += 1
    if x == n and c == 'a':
        break
    elif count == n and c == 'b':
        break

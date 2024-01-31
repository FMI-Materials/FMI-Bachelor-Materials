# exercitiul 1

# time complexity: O(2^n)
# space complexity: O(n)

def fibo(n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    return fibo(n-1) + fibo(n-2)

# exercitiul 2

# time complexity: O(n)
# space complexity: O(n)

def fibo2(n):
    global fibonacci

    if len(fibonacci) == n + 1:
        return fibonacci[n]
    else:
        fibonacci.append(fibonacci[-1] + fibonacci[-2])
        return fibo2(n)

# exercitiul 3

def fibo3(n):

    prev = 0
    current = 1

    for i in range (n - 1):
        prevprev = prev
        prev =  current
        current = prevprev + prev

    return current

fibonacci = [0, 1]

n = int(input())

print(f"Exercitiul 1: {fibo(n)}")
print(f"Exercitiul 2: {fibo2(n)}")
print(f"Exercitiul 3: {fibo3(n)}")
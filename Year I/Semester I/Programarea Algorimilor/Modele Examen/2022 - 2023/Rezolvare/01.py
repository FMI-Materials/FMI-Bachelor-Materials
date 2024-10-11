# a

def divizori(*arg):
    d = {}
    for nr in arg:
        aux = nr
        f = 2
        l = []
        while aux > 1:
            if aux % f == 0:
                l.append(f)
            while aux % f == 0:
                aux //= f
            f += 1
        d[nr] = l
    return d

# b

litere_10 = [chr(ord('a') + i) for i in range(10)]

# c

# T(n) = 1 * T(n/3) + 1 => f(n) = functie constanta => 
# => p = 0, b = 3, a = 1
# p = 0 == logb(a) = 0 => (Teorema de master) T(n) = O(log2(n))


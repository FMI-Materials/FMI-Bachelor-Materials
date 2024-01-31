import random

class Chromosome:
    def __init__(self, a, b, n, bits, precision = 0):
        self.a = a
        self.b = b
        self.n = n
        self.bits = bits
        self.precision = (b - a) / (2 ** n)

    def transform(self):
        string = "".join([str(x) for x in self.bits])

        n = int(string, 2)
        n = n * self.precision

        return self.a + n

def randomBits (n, length):
    lista = []
    for i in range(n):
        bits = []
        for i in range(length):
            bits.append(random.randint(0,1))
        lista.append(bits)
    
    return lista

# a = 2, b = 3, n = 3, bits = [1,1,1], p = 0.125
# transform: bits = 7, 0.125 * 7 = 0.875, a = 2 + 0.875 = 2.875
c1 = Chromosome(2,3,3,[1,1,1])
# print(c1.a)
c1.transform()
# print(c1.a)

# a = 1, b = 4, n = 3, bits = [1,0,1], p = 0.375
# transform: bits = 5, 0.375 * 5 = 1.875, a = 1 + 1.875 = 2.875
c2 = Chromosome(1,4,3,[1,0,1])
# print(c2.a)
c2.transform()
# print(c2.a)

c3 = Chromosome(-1, 2,22, [0,0,0,0,0,1,1,1,0,1,0,0,1,0,0,1,1,1,0,0,0,1])
# print(c3.transform())

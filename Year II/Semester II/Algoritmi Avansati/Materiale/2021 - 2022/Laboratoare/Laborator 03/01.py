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

#
# functii pentru algoritmul de evolutie
#

def populatieInitiala():
    g.write("Populatia initiala:\n")
    for i in range(n):
        string = ""
        bits = [str(x) for x in ch[i]]
        bits = "".join(bits)
        string = string + str(i) + ": " + bits + " "
        string = string + "x = " + str(x[i]) + " "
        string = string + "f = " + str(f[i]) + "\n"
        g.write(string)
    g.write("\n")

def probabilitateSelectie():
    sumProb = sum(f)
    probabilitati = []
    g.write("Probabilitate selectie:\n")
    for i in range(n):
        string = "cromozom " + str(i) + ": probabilitate = "
        p = f[i] / sumProb
        probabilitati.append(p)
        string = string + str(p) + "\n"
        g.write(string)
    g.write("\n")
    probabilitati.sort()
    return probabilitati

def intervaleProbabilitati(p):
    intervale = [0]
    g.write("Intervale probabilitate selectie:\n")
    g.write("0 ")
    for i in range(len(p) - 1):
        interv = intervale[-1] + p[i]
        intervale.append(interv)
        g.write(str(interv))
        g.write(" ")
    g.write("1")
    g.write("\n")
    return intervale

def cautareBinara(intervale, left, right, x):
    if right - left == 1:
        return left
    else:
        mid = (left + right) // 2
        if x > intervale[mid]:
            return cautareBinara(intervale, mid, right, x)
        else:
            return cautareBinara(intervale, left, mid, x)

def selectie(intervale, populatieVeche):
    cromozomiSelectati = []
    for i in range(n):
        u = random.random()
        cromozom = cautareBinara(intervale, 0, len(intervale), u)
        cromozomiSelectati.append(cromozom)
        g.write(f'\nu = {u}, selectam cromozomul {cromozom}')
    g.write("\n")

    g.write('\nPopulatia dupa selectie:\n')
    populatieNou = [0] * n
    for i, cromozom in enumerate(cromozomiSelectati):
        cromozomNou = populatieVeche[cromozom - 1]
        populatieNou[i] = cromozomNou
        xNou = cromozomNou.transform()
        fNou = f[cromozom - 1]
        bits = [str(x) for x in cromozomNou.bits]
        bits = "".join(bits)
        g.write(f'{i+1}: {bits} x = {xNou} f = {fNou}\n')
        
    return populatieNou

#
# main entry
#

g = open("evolutie.txt", "w")

# 20 de cromozomi de lungime 22
n = 20
ch = randomBits(n, 22)

# se creeaza lista de cromozomi cu
# valorile random generate anterior

cromozomi = []
for i in range(n):
    c = Chromosome(-1, 2, 22, ch[i])
    cromozomi.append(c)

x = [c.transform() for c in cromozomi]
f = [(-1) * (x**2) + x  + 2 for x in x]

populatieInitiala()
probabilitati = probabilitateSelectie()
intervale = intervaleProbabilitati(probabilitati)
cromozomi = selectie(intervale, cromozomi)

g.close()
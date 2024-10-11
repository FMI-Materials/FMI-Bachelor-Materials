import numpy as np
import matplotlib.pyplot as plt
import math

""" Variabile aleatoare discrete si continue
        variabila discreta = variabila care ia valori dintr-o multime discreta (cel mult numarabila (finita, sau numarabila))
            - binomiala (modeleaza posibilitatea unui eveniment sa se intample pana in primii k pasi)
            - geometrica (modeleaza posibilitatea unui eveniment sa se intample la pasul k)
            - poisson (modeleaza nr. de succese dintr-un interval de timp stiind ca in medie avem lambda succese)
                <=> Bin(n, lambda/n) unde n tinde la infinit
        variabila continua
            - exponentiala (modeleaza timpul de asteptare pana cand un anumit eveniment are loc
                            stiind ca in medie timpul de asteptare este 1/lambda)
"""
def ex1():
    def a():
        N = 1_000_000
        n = 1_000_000
        _lambda = 30
        
        pois = np.random.binomial(n,_lambda/n,N)
        pois_patrat = np.square(pois)

        medie = np.sum(pois)/N
        medie_patrat = np.sum(pois_patrat)/N

        print("E(X) =",medie)
        print("E(X^2) =", medie_patrat)
        print("E(X)^2 =",np.square(medie))
        print("VAR(X) =", medie_patrat - np.square(medie))
        print("n*lambda(1-lambda) =", n*(_lambda/n)*(1-(_lambda/n)))

        plt.hist(pois, bins=100, density=True)
        plt.show()

    def d():
        n = 50
        _lambda = 20
        pois = [0] * n
        index = [i for i in range(n)]

        for i in range(n):  
            pmf = np.exp(-_lambda) * pow(_lambda,i) / math.factorial(i)
            pois[i] = pmf

        mean = sum(i * pois[i] for i in range(len(pois)))
        variance = sum((i - mean)**2 * pois[i] for i in range(len(pois)))

        print("E(X) =",mean)
        print("VAR(X) =", variance)
        print("n*lambda(1-lambda) =", n*(_lambda/n)*(1-(_lambda/n)))
        
        plt.plot(index, pois, '-o')
        plt.show()

    d()

def ex2():
    N = 1_000_000
    n = 1_000_000
    _lambda = 150

    pois = np.random.binomial(n,_lambda/n,N)
    prob = np.mean(pois <= _lambda)

    print("Probabilitate =",1 - prob)


def ex4():
    def a():
        N = 100_000
        _lambda = 50

        U = np.random.uniform(0,1,N)
        exp = (-1/_lambda) * np.log(U)

        plt.hist(exp,bins=100,density=True)
        plt.show()

    def b():
        N = 100_000
        _lambda = 20

        exp = np.random.exponential(scale=1.0, size=N)
        
        plt.hist(exp, bins=100, density=True)
        plt.show()

    a()

def ex5():
    N = 1_000_000
    _lambda1 = 2.5
    _lambda2 = 5

    exp1 = np.random.exponential(scale=_lambda1,size=N)
    exp2 = np.random.exponential(scale=_lambda2,size=N)

    prob1 = np.mean(exp1 <= _lambda1)
    prob2 = np.mean(exp2 <= _lambda2)

    print("telefon1 =",1-prob1)
    print("telefon2 =",1-prob2)

ex5()
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

        pois = np.random.binomial(n, _lambda / n, N)
        pois_patrat = np.square(pois)

        medie = np.sum(pois) / N
        medie_patrat = np.sum(pois_patrat) / N

        print("E(X) =", medie)
        print("E(X^2) =", medie_patrat)
        print("E(X)^2 =", np.square(medie))
        print("VAR(X) =", medie_patrat - np.square(medie))
        print("n*lambda(1-lambda) =", n * (_lambda / n) * (1 - (_lambda / n)))

        plt.hist(pois, bins=100, density=True)
        plt.show()

    def d():
        n = 50
        _lambda = 20
        pois = [0] * n
        index = [i for i in range(n)]

        for i in range(n):
            pmf = np.exp(-_lambda) * pow(_lambda, i) / math.factorial(i)
            pois[i] = pmf

        mean = sum(i * pois[i] for i in range(len(pois)))
        variance = sum((i - mean) ** 2 * pois[i] for i in range(len(pois)))

        print("E(X) =", mean)
        print("VAR(X) =", variance)
        print("n*lambda(1-lambda) =", n * (_lambda / n) * (1 - (_lambda / n)))

        plt.plot(index, pois, '-o')
        plt.show()

    d()


def ex2():
    N = 1_000_000
    n = 1_000_000
    _lambda = 150

    pois = np.random.binomial(n, _lambda / n, N)
    prob = np.mean(pois <= _lambda)

    print("Probabilitate =", 1 - prob)


def ex4():
    def a():
        N = 100_000
        _lambda = 50

        U = np.random.uniform(0, 1, N)
        exp = (-1 / _lambda) * np.log(U)

        plt.hist(exp, bins=100, density=True)
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

    exp1 = np.random.exponential(scale=_lambda1, size=N)
    exp2 = np.random.exponential(scale=_lambda2, size=N)

    prob1 = np.mean(exp1 <= _lambda1)
    prob2 = np.mean(exp2 <= _lambda2)

    print("telefon1 =", 1 - prob1)
    print("telefon2 =", 1 - prob2)


# ----- LAB 08 -----
def exercitiu1(niu, sigma):
    N = 10_000
    
    def normala1(niu, sigma):
        X = [0] * N
        for i in range(N):
            X[i] = niu + np.sqrt((-2) * sigma**2 * np.log(np.random.uniform(0, 1))) * \
                         np.cos(2 * np.pi * np.random.uniform(0, 1))
                         
        return X
    
    def normala2(niu, sigma):
        X = [0] * N
        for i in range(N):
            X[i] = niu + np.sqrt((-2) * sigma**2 * np.log(np.random.uniform(0, 1))) * \
                         np.sin(2 * np.pi * np.random.uniform(0, 1))

        return X
    
    f = lambda x: 1/(np.sqrt(2*np.pi*sigma)) * np.exp((-(x-niu)**2)/(2*sigma))
    
    X = normala1(niu, sigma)
    Y = normala2(niu, sigma)
    Z = np.random.normal(0, 1, size=N)
    
    mean = sum(X) / N
    Xsquarred = np.square(X)
    mean_squarred = sum(Xsquarred) / N
    variance = mean_squarred - np.square(mean)

    print("E(X) =", mean)
    print("VAR(X) =", variance)
    
    x = np.linspace(-4, 4, 1000)
    y = f(x)
    
    plt.hist(X, bins=100, density=True, label='X', color='blue', alpha=0.5)
    plt.hist(Y, bins=100, density=True, label='Y', color='red', alpha=0.5)
    plt.hist(Z, bins=100, density=True, label='Z', color='green', alpha=0.5)
    plt.plot(x, y, color = 'black', label = 'f(x)')
    plt.show()


# exercitiu1(0, 1)

def exercitiu2(niu, sigma, alfa, beta):
    N = 100_000
    X = np.random.normal(niu, sigma, size=N)
    Y = alfa + X
    Z = beta * X
    W = alfa + beta * X

    f = lambda x: 1/(np.sqrt(2*np.pi*sigma)) * np.exp((-(x-(alfa + niu))**2)/(2*sigma))
    g = lambda x: 1/(np.sqrt(2*np.pi*beta**2*sigma)) * np.exp((-(x-(beta * niu))**2)/(2*sigma**2*beta**2))
    h = lambda x: 1/(np.sqrt(2*np.pi*beta**2*sigma)) * np.exp((-(x-(alfa + beta * niu))**2)/(2*sigma**2*beta**2))

    x = np.linspace(-40, 40, 1000)
    y = f(x)
    t = g(x)
    u = h(x)

    plt.hist(Y, bins=100, density=True, label='a', color='blue', alpha=0.5)
    plt.hist(Z, bins=100, density=True, label='b', color='red', alpha=0.5)
    plt.hist(W, bins=100, density=True, label='c', color='green', alpha=0.5)
    plt.plot(x, y, color = 'black', label = 'f(x)')
    plt.plot(x, t, color = 'yellow', label = 'g(x)')
    plt.plot(x, u, color = 'purple', label = 'h(x)')
    plt.show()


# exercitiu2(0, 1, 5, 10)

def exercitiu3(niu, sigma):
    N = 1_000
    n = 500

    lam = 3
    X = np.random.poisson(lam, size=(N, n))
    mu = lam
    var = lam

    def CLT(X, mu, var):
        sample_means = np.mean(X, axis=1)

        theoretical_mean = mu
        theoretical_std = np.sqrt(var / n)

        plt.figure(figsize=(8, 6))

        plt.hist(sample_means, bins=30, density=True, alpha=0.7, color='blue')

        normal_distribution = np.random.normal(theoretical_mean, theoretical_std, 1000)
        plt.hist(normal_distribution, bins=30, density=True, alpha=0.5, color='red')

        # f = lambda x: 1/(np.sqrt(2*np.pi*mu**2)) * np.exp(-(x**2)/(2*mu**2))
        # x = np.linspace(-4,4,1000, axis=0)
        # y = f(X)
        #
        # plt.plot(x, y, color = 'purple', label = 'f(x)')
        
        plt.title('Central Limit Theorem Demonstration')
        plt.xlabel('Sample Means')
        plt.ylabel('Frequency')
        plt.legend(['Sample Means', 'CLT Normal Approximation'])
        plt.show()

    CLT(X, mu, var)


exercitiu3(0, 1)
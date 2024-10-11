import math

import numpy as np
import matplotlib.pyplot as plt
import scipy as sp

# care este parametrul necunoscut ?
# normal = Normal(p) => p = ?

"""
Idee: Asociem o functie(functie de verosimilitate -> likelihood)
L(x1,x2,...,xn, p)
vreau p ai. fct. de verosimilitate sa fie maxima
L(x1,x2,...,xn,p) = produs i=1,n din f(xi,p) -> functia de densitate sau ponderile (continua sau discreta)
ex: pentru Bernoulli(p) p=0,1
    X ~ 0   1
        1-p p 
    f(x,p) = {
        p, x = 1
        1-p, x = 0
    }
    
    *f(x,p) = p^x (1-p)^(1-x)
    
OBS: L >= 0         | => p = ag max L(x1,...,xn,p)
log e strict cresc  |       este arg max log L(x1,...,xn,p) = Suma i=1,n din log f(xi,p) =>
=> Suma i=1,n din log (p^xi (1-p)^(1-xi))
=> Suma i=1,n din log(p^xi) + log ((1-p)^(1-xi))
=> Suma i=1,n din (xi) + log(1-p)*Suma i=1,n din (1-xi)

derivam in raport cu p pentru a obtine punctele de maxim din punctele critice
Slog(L(x1,...,xn,p)) = 0
1/p * Suma i=1,n din x - 1/(1-p) * Suma i=1,n din (1-xi)
(1-p)/p = Suma i-1,n din (1-xi) / Suma i=1,n din xi
1/p - 1 = n / Suma i=1,n din xi -1
p = Suma i=1,n din xi / n => momentan p este doar punct critic (sa vedem ca e de maxim => derivata 2)

 """
normal = np.load('sample_Normal.npy')
exponential = np.load('sample_Exp.npy')
geometrical = np.load('sample_Geom.npy')
poisson = np.load('sample_Poisson.npy')
bernoulli = np.load('sample_Bernoulli.npy')

# 1. afisati histograma datelor
# 2. afisati graficul functiei de verosimilitate
# 3. determinati estimarea p pt parametrul distributiei bernoulli
# 4. pe graficul functiei afisam valoarea minima si maxima (p, logL(p))

def functie_bernoulli():
    plt.hist(bernoulli, bins=30, density=True)
    plt.show()

    theta = np.linspace(0.00001,0.99999,100)
    median = np.mean(bernoulli)
    logL = []
    for t in theta:
        logL.append(np.sum(bernoulli * np.log(t) + (1 - bernoulli) * np.log(1 - t)))
    plt.plot(theta, logL)
    plt.show()

    plt.plot(theta, logL)
    plt.plot(median, np.sum(bernoulli * np.log(median) + (1 - bernoulli) * np.log(1 - median)), 'ro')
    plt.show()

    max_index = np.argmax(logL)
    min_index = np.argmin(logL)

    plt.plot(theta, logL)
    plt.plot(theta[max_index], logL[max_index], 'ro')  # Punctul maxim
    plt.plot(theta[min_index], logL[min_index], 'bo')  # Punctul minim

    plt.show()

def functie_poisson():
    plt.hist(poisson, bins=30, density=True)
    plt.show()

    n = len(poisson)
    theta = np.linspace(0,50,100)
    median = np.mean(poisson)
    logL = []
    for t in theta:
        logL.append(-1 * n * t + np.log(t) * np.sum(poisson) - np.sum(np.log(sp.special.factorial(poisson))))
    plt.plot(theta, logL)
    plt.show()

    plt.plot(theta, logL)
    plt.plot(median, -1 * n * median + np.log(median) * np.sum(poisson) - np.sum(np.log(sp.special.factorial(poisson))), 'ro')
    plt.show()

    max_index = np.argmax(logL)
    min_index = np.argmin(logL)

    plt.plot(theta, logL)
    plt.plot(theta[max_index], logL[max_index], 'ro')  # Punctul maxim
    plt.plot(theta[min_index], logL[min_index], 'bo')  # Punctul minim

    plt.show()

def functie_geometrica():
    plt.hist(geometrical, bins=30, density=True)
    plt.show()

    n = len(geometrical)
    theta = np.linspace(0.00001,0.99999,100)
    median = n / np.sum(geometrical)
    logL = []
    for t in theta:
        logL.append(n * np.log(t) + np.log(1-t) * np.sum(geometrical - 1))
    plt.plot(theta, logL)
    plt.show()

    plt.plot(theta, logL)
    plt.plot(median,n * np.log(median) + np.log(1-median) * np.sum(geometrical - 1), 'ro')
    plt.show()

    max_index = np.argmax(logL)
    min_index = np.argmin(logL)

    plt.plot(theta, logL)
    plt.plot(theta[max_index], logL[max_index], 'ro')  # Punctul maxim
    plt.plot(theta[min_index], logL[min_index], 'bo')  # Punctul minim

    plt.show()

def functie_exponentiala():
    plt.hist(exponential, bins=30, density=True)
    plt.show()

    n = len(exponential)
    theta = np.linspace(0,50,100)
    median = n / np.sum(exponential)
    logL = []
    for t in theta:
        logL.append(n * np.log(t) - t * np.sum(exponential))
    plt.plot(theta, logL)
    plt.show()

    plt.plot(theta, logL)
    plt.plot(median,n * np.log(median) - median * np.sum(exponential), 'ro')
    plt.show()

    max_index = np.argmax(logL)
    min_index = np.argmin(logL)

    plt.plot(theta, logL)
    plt.plot(theta[max_index], logL[max_index], 'ro')  # Punctul maxim
    plt.plot(theta[min_index], logL[min_index], 'bo')  # Punctul minim

    plt.show()

# functie_bernoulli()
# functie_poisson()
# functie_exponentiala()

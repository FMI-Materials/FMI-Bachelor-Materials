import numpy as np
import matplotlib.pyplot as plt

def ex1():
    n = 1_000
    N = 100_000
    
    def a(lower, upper, f):
        x = np.linspace(lower, upper, 1_000)
        y = f(x)
        
        plt.figure()
        plt.plot(x,y, color='black', label='f(x)')
        plt.show()
        
    def d(a, b, n, N, f):
        X = np.random.uniform(a,b,size=(N,n))
        
        aproximare_integrala = np.mean((f(X) * (b-a)),axis=1)
        
        plt.hist(aproximare_integrala, density=True, bins=50)
        plt.show()
      
    f = lambda x: np.exp(-(x**2))
    # a(0,1,f)
    d(0, 1, n, N, f)
    
    
# ex1()


def ex2():
    n = 1_000
    N = 100_000

    def a(lower, upper, f):
        X = np.random.uniform(lower,upper,size=(N,n))
        
        importanta = f(X) / np.sqrt(2 * np.pi)
        aproximare_integrala = np.mean(f(X) * importanta, axis=1)
        
        plt.hist(aproximare_integrala, density=True, bins=50)
        plt.show()
        
    f = lambda x: np.exp(-(x**2))
    a(0,1,f)
    
    
ex2()

def ex3():
    def a(lower, upper, f):
        x = np.linspace(lower, upper, 1_000)
        y = f(x)
        
        plt.plot(x, y, color='black', label='f(x)')
        plt.show()
        
    f = lambda x: np.sin(2*x) + 0.3*np.cos(10*x) + 0.05*np.sin(100*x)
    a(0,5,f)
    
    
# ex3()


# importance sampling
# filtru gaussio
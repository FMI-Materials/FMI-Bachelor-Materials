import numpy as np
import matplotlib.pyplot as plt

def method1():
    N = 1000
    plt.figure()
    plt.xlim([-1,1])
    plt.ylim([-1,1])
    plt.axis('equal')
    plt.title('Method 1: Random midpoint on a radius')

    n = 0
    for i in range(N):
        theta = 2*np.pi * np.random.rand()
        r = np.random.rand()
        m = np.array([r*np.cos(theta),r*np.sin(theta)])

        lm = np.sqrt(m[1]**2 + m[0]**2)
        if lm < 1/2:
            n += 1
        
        a = -m[0]/m[1]
        b = m[1] - a*m[0]
        delta = 4 * a**2 * b**2 - 4*(1 + a**2) * (b**2 - 1)

        x = np.array([(-2*a*b + np.sqrt(delta))/(2*(1+a**2)), (-2*a*b-np.sqrt(delta))/(2*(1+a**2))])
        y = a*x+b

        plt.plot(x,y,'C0', linewidth = 0.5) 
        plt.plot(x,y,'.') 
        plt.plot(m[0],m[1],'C1.')

    P = n/N
    print('method 1 : P = ',P) 
    plt.show()

def method2():
    N = 1000
    plt.figure()
    plt.xlim([-1,1])
    plt.ylim([-1,1])
    plt.axis('equal')
    plt.title('Method 2: Uniform midpoint on a radius')

    n=0
    for i in range(N):
        theta = 2*np.pi * np.random.rand()
        r = np.sqrt(np.random.rand())
        m = np.array([r*np.cos(theta),r*np.sin(theta)])

        lm = np.sqrt(m[1]**2 + m[0]**2)
        if lm < 1/2:
            n += 1

        a = -m[0]/m[1]
        b = m[1] - a*m[0]
        delta = 4 * a**2 * b**2 - 4*(1 + a**2) * (b**2 - 1)

        x = np.array([(-2*a*b + np.sqrt(delta))/(2*(1+a**2)), (-2*a*b-np.sqrt(delta))/(2*(1+a**2))])
        y = a*x+b

        plt.plot(x,y,'C0', linewidth = 0.5) 
        plt.plot(x,y,'.') 
        plt.plot(m[0],m[1],'C1.')

    P = n/N
    print('method 1 : P = ',P) 
    plt.show()

method2()
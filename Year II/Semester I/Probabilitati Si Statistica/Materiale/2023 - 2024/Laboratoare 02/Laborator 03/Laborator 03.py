import numpy as np
import matplotlib.pyplot as plt

def ex1():
    def a(a,b):
        N = 1000
        n = 0
        for i in range(N):
            x = np.random.uniform()
            if x >= a and x <= b:
                n += 1
        print(n/N)
    a(0.37,0.82)

def ex3():
    def method1(d,r,N):
        R = 2*r
        X = np.random.uniform(-R/2,R/2,size = (d,N))

        # inmultire cu 1 pentru a obtine numar din expresie true/false
        n = np.sum(1*(np.linalg.norm(X,axis=0) <= r))

        P = n/N
        volume = P * R ** d
        print("Volume of ",d,"D ball with r = ",r,": ",volume,sep='') 

        # plt.figure()
        # plt.axis('equal')
        # plt.plot(X[0,:],X[1,:],'.')

        # indicii unde norma e mai mica decat r
        ind = np.where(np.linalg.norm(X,axis=0) <= r)
        # plt.plot(X[0,ind],X[1,ind],'C1. ')

        # plt.show()

    for i in range(2,10):
        method1(i,1,10)


def ex6():
    def method1():
        center = (0,0)
                
        plt.figure()
        plt.xlim([-1,1])
        plt.ylim([-1,1])
        plt.axis('equal')
        plt.title('Shape 1')

        N = 1000
        for i in range(N):
            x = np.random.uniform(-1,1)
            y = np.random.uniform(-1,1)

            if x**2 + y**4 + 2*x*y - 1 <= 0:
                plt.plot(x,y,'.')

        plt.show()

    def method2():
        center = (0,0)
        a = 3
                
        plt.figure()
        plt.xlim([-1,1])
        plt.ylim([-1,1])
        plt.axis('equal')
        plt.title('Shape 2')

        N = 10000
        n = 0
        for i in range(N):
            x = np.random.uniform(-a,a)
            y = np.random.uniform(-a,a)

            if y**2 + x**2*np.cos(x) - 1 <= 0:
                n += 1   
                plt.plot(x,y,'.')

        P = n/N
        Area = P * (2*a)**2
        print("Area:",Area)
        plt.show()

    # more efficient
    def method3():
        plt.figure()
        plt.axis('equal')
        plt.title('Shape 3')

        a = 3

        f = lambda x,y: np.exp(x**2) + y**2 - 4 + 2.99*np.cos(y)

        N = 10000
        x = np.random.uniform(-a,a,size=N)
        y = np.random.uniform(-a,a,size=N)

        n = np.sum(1*(f(x,y)<= 0))

        P = n/N
        Area = P * (2*a)**2
        print("Area:",Area)

        plt.plot(x,y,'.')

        ind = np.where(f(x,y) <= 0)
        plt.plot(x[ind],y[ind],'.')        

        plt.show()

    method3()


ex6()
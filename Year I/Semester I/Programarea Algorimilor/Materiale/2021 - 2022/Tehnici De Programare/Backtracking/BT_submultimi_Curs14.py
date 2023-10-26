#submultimile unei multimi date
#submultimile multimii {1,2,...,n}
#submultimi = combinari de n luate cate m=0,1,2,3,...n
#sumbmultime - vector caracteristic - binar de lungime n 00010.1..0 elementul i este in multime <=>xi=1

#pb se reduce la a genera toate sirurile binare de lungime n folosind backtracking:
#reprez sol x=(x0,...,x_{n-1})
#valori pt xk - 0 sau 1
#cond final - nimic
#cond continuare - nimic
def back(k):
    if k==n:
        #print(*x)
        print([a[i] for i in range(n) if x[i]==1])
    else:
        #dam valoare lui x[k]:
        for i in range(0,2):
            x[k]=i
            back(k+1)

a=[3,1,7,9]
n=len(a)
x=[0 for i in range(n)]
back(0)

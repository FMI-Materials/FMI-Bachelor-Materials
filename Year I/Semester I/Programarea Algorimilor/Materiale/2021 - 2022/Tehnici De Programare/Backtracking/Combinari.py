"""
COMBINARI(n,m) - ale multimii {1,2,..n}
n=4,m=3
1 2 3
1 2 4
1 3 4
2 3 4

submultimi  cu m elemente (distincte):
1,2,3 = 1,3,2
1,2,4...
Reprezentare solutie:
x=(x0,...,x_{m-1}) - o subm cu m elemente
Fiecare pozitie xk poate lua valori de la 1 la n
Cond finale - elemente distincte + in ordine crescatoare
Cond de continuare la pasul k (valid(k)): xk > xk-1 (paentru k>0) - crescator

SE modifica programul de aranjamanete punand conditia x[k]>x[k-1]-crescator
"""
def back(k):
    if k==m:
        #if conditii_finale(x): - nu este necesar niciun test suplimentar, conditiile de continuare sunt suficiente
        print(*x)
    else:
        #dam valoare lui x[k]:
        """
        for i in range(1,n+1):
            x[k]=i
            #if valid(k):

            if (k==0) or (x[k] > x[k-1]):
                back(k+1)
        """
        #putem da valori lui x[k]incepand cu x[k-1]+1
        if k==0:
            start=1
        else:
            start=x[k-1]+1
        for i in range(start, n + 1):
            x[k] = i
            back(k + 1)


n=5
m=3
x=[0 for i in range(m)]
back(0)


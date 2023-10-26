"""
ARANJAMENTE(n,m) - ale multimii {1,2,..n}
n=4,m=3
submultimi ordonate cu m elemente:
1,2,3 != 1,3,2
1,2,4...
Reprezentare solutie:
x=(x0,...,x_{m-1}) - un aranjament #!!nu m
Fiecare pozitie xk poate lua valori de la 1 la n
Cond finale - elemente distincte
Cond de continuare la pasul k (valid(k)): xk sa fie diferit de x0...xk-1

SE modifica programul de permutari inlocuind doar lungimea lui x
"""
def back(k):
    if k==m:
        #if conditii_finale(x): - nu este necesar niciun test suplimentar, conditiile de continuare sunt suficiente
        print(*x)
    else:
        #dam valoare lui x[k]:
        for i in range(1,n+1):
            x[k]=i
            #if valid(k):

            if x[k] not in x[:k]:
                back(k+1)
            """
            try:
                x.index(x[k],0,k)
            except:
                back(k + 1)
            """


n=4
m=3
x=[0 for i in range(m)]
back(0)

#var 2 - pentru a nu verifica daca xk sa fie diferit de x0...xk-1 comparand xk cu toate aceste elemente
#putem mentine un vector de frecvente/aparitii in care marcam numerele pe care le-am folosit deja

def back2(k):
    if k == m:
        #print(*x)
        print([elevi[x[i]-1] for i in range(m)])
    else:
        # dam valoare lui x[k]:
        for i in range(1, n + 1):
            x[k] = i
            if v[x[k]]==0: #if x[k] not in x[:k]:
                v[x[k]]  = 1
                back2(k + 1)
                v[x[k]] = 0



n = 4
elevi=["Ion","Ioana","Mihai","Mihaela"]
m=3
x = [0 for i in range(m)]
v = [0 for i in range(n+1)]
print("varianta 2")
back2(0)
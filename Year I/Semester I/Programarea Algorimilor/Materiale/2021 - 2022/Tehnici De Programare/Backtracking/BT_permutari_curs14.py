"""
PERMUTARI(n)
Reprezentare solutie:
x=(x0,...,x_{n-1}) - o permutare
Fiecare pozitie xk poate lua valori de la 1 la n
Cond finale - elemente distincte
Cond de continuare la pasul k (valid(k)): xk sa fie diferit de x0...xk-1
"""
def back(k):
    if k==n: #am completat x0,...,x_{n-1}, incerc sa completez xn => am terminat de completat x
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
x=[0 for i in range(n)]
back(0)

#var 2 - pentru a nu verifica daca xk sa fie diferit de x0...xk-1 comparand xk cu toate aceste elemente
#putem mentine un vector de frecvente/aparitii in care marcam numerele pe care le-am folosit deja

def back2(k):
    if k == n:  # am completat x0,...,x_{n-1}, incerc sa completez xn => am terminat de completat x
        # if conditii_finale(x): - nu este necesar niciun test suplimentar, conditiile de continuare sunt suficiente
        print(*x)
    else:
        # dam valoare lui x[k]:
        for i in range(1, n + 1):
            x[k] = i
            if v[x[k]]==0: #if x[k] not in x[:k]:
                v[x[k]]  = 1
                back2(k + 1)
                v[x[k]] = 0



n = 4
x = [0 for i in range(n)]
v = [0 for i in range(n+1)]
print("varianta 2")
back2(0)

#EXERCITIU - permutarile care incep cu un numar dat k

n = 4
x = [0 for i in range(n)]
v = [0 for i in range(n+1)]
k=2
print("permutari care incep cu ",k)
x[0]=k
v[k]=1
back2(1) #nu cu 0

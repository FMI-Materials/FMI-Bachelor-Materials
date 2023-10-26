"""
n - toate modalitatile de a scrie n ca suma de numere naturale nenule
(cu obs ca ordinea termenilor in descompunere nu conteaza)
n=4:
1+1+1+1
1+1+2 = 1+2+1
1+3
2+2
4
Reprezentare
x=x0,x1,..xk (lungime variabila)  reprezentand termeni din descompunere
xk poate lua valorile: 1,2,..,n
cond finala: suma x0+...xk=n si valorile din x sa fie ordonate crescator (nestrict): x0<=x1<=...<=xk
cond de continuare:  x0+...xk<=n si xk>=x_{k-1}
"""
def back(k):
    if sum(x[:k]) == n: #nu mai are lungime fixa, este solutie daca are suma n
        print(*x[:k])
    else:
        if k==0:
            start=1
        else:
            start=x[k-1]
        for i in range(start,n+1):
            x[k]=i
            if sum(x[:k+1])<=n:
                back(k+1)

n=4
x=[0 for i in range(n)]
print("varianta 1 - cu suma calculata de fiecare data")
back(0)

#varianta 2 - nu calculam de fiecare data sum(x[:k+1]), ci actualizam suma curenta in functie de valoarea lui x[k]

def back2(k):
    global suma
    if suma == n: #nu mai are lungime fixa, este solutie daca are suma n
        print(*x[:k])
    else:
        if k==0:
            start=1
        else:
            start=x[k-1]
        for i in range(start,n+1):
            x[k]=i
            suma += x[k] #suma += 1
            if suma <= n:
                back2(k+1)
            suma -= x[k]

n=4
suma=0
x=[0 for i in range(n)]
print("varianta 2 - cu suma actualizata")
back2(0)
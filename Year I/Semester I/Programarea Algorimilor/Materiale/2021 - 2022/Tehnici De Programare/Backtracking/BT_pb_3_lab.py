"""
Pentru elaborarea unui test de aptitudini avem un set de n întrebări,
fiecare fiind cotată cu un număr de puncte dat.
Să se elaboreze toate chestionarele având a întrebări distincte, fiecare chestionar totalizând p puncte.
Întrebările sunt date prin număr şi punctaj. Nu se ţine cont de ordinea întrebărilor în chestionar
(de exemplu chestionarul cu întrebările 1 şi 2 este acelaşi cu chestionarul cu întrebările 2 şi 1)

vrem a intrebari din n + nu conteaza ordinea => combinari
vrem doar punctaj total p => conditie legata de suma punctajului, ca la partitiile lui n
"""
def back(k):
    global suma
    if k==m:
        if suma ==p:
            print(*x)
    else:
        if k==0:
            start=1
        else:
            start=x[k-1]+1
        for i in range(start, n + 1):
            x[k] = i
            suma+=pct[x[k]-1] #indicii din x sunt de la 1
            if suma<=p:
                back(k + 1)
            suma-= pct[x[k] - 1]

n=6
m=3
p=10 #punctajul total
suma=0
pct=[1,4,2,3,5,4]
x=[0 for i in range(m)]
back(0)
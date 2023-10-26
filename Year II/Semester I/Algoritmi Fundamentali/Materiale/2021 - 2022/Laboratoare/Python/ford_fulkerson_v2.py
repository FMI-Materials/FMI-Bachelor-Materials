'''
    Testare graf bipartit folosind BFS
    Cuplajul maxim folosindu-ma de bipartitie si de EK
    pentru fiecare arc cu flux nenul xy din N care nu este
    incident în s sau t, muchia xy corespunzătoare din G se
    adaugă la M)
    TREBUIE FACUT CU GRAF REZIDUAL
'''
def BFS():
    global graf, s, t, n, parent
    visited = [False] * (n+2)
    queue = []
    queue.append(s)
    visited[s] = True
    while queue:
        u = queue.pop(0)
        for ind, val in enumerate(graf[u]):
            if visited[ind] == False and val > 0:
                queue.append(ind)
                visited[ind] = True
                parent[ind] = u
    return True if visited[t] else False

def FordFulkerson():
    global graph, s, t, n, parent

    max_flow = 0

    while BFS():
        path_flow = float("Inf")
        cs = t
        while cs != s:
            path_flow = min(path_flow, graf[parent[cs]][cs])
            cs = parent[cs]

        max_flow += path_flow

        v = t
        while v != s:
            u = parent[v]
            graf[u][v] -= path_flow #arc direct
            graf[v][u] += path_flow #arc invers
            v = parent[v]

    return max_flow
def BIPARTIT():
    global n, graf, start, culoare
    culoare[start] = 1 #colorez primul nod (o sa alternez culorile 0 si 1 )

    coada = []
    coada.append(start)

    while len(coada)>0:
        u = coada.pop()
        if graf[u][u] == 1: #daca s-a scos pe sine
            return False
        for v in range(1,n+1):
            if graf[u][v] == 1 and culoare[v] == -1:#nu a fost colorat
                culoare[v] = 1 - culoare[u]
                coada.append(v)
            #muchie de la u la v cu u si v cu aceeasi culoare => nu e bipartit
            elif graf[u][v] == 1 and culoare[v] == culoare[u]:
                return False
    return True

n=4
#desi sunt 4 adaug cate 2 linii si cate 2 coloane in plus ca sa am
#pt s si t
graf= [
#    s  1  2  3  4  t
    [0, 0, 0, 0, 0, 0], #s
    [0, 0, 1, 0, 1, 0], #1
    [0, 1, 0, 1, 0, 0], #2
    [0, 0, 1, 0, 1, 0], #3
    [0, 1, 0, 1, 0, 0], #4
    [0, 0, 0, 0, 0, 0]  #t
        ]
start=1
culoare = [-1] * (n+1)
if BIPARTIT()==True:
    print("Graful este bipartit")
    # despart varfurile in 2 multimi in functie de culori
    for i in range(1, n + 1):
        if culoare[i] == 1:
            # conectez s-> i
            graf[0][i] = 1
        else:
            # conectez i->t
            graf[i][n + 1] = 1

    s = 0  # S
    t = 5  # T
    parent = [-1] * (n + 2)
    print("Max flow: ", FordFulkerson())
    #un graf bipartit nu contine nicun ciclu de lungime impara
    #mai am muchiile de afisat
    '''
    pentru fiecare arc cu flux nenul xy din N care nu este
incident în s sau t, muchia xy corespunzătoare din G se
adaugă la M) => alg cu graf-ul rezidual
fluxul pt fiecare arc se ia din graful rezidual final:
pentru arcul xy de pe arcul yx din graful rezidual
    '''

else:
    print("Graful NU este bipartit")
    # lungime ciclu impar
    viz = [0] * (n + 1)
    afisare=[]
    tata = [0] * (n + 1)
    ok = 0
    nr=None
    def DF(x):
        global ok, graf, tata, viz, afisare, nr
        viz[x] = 1
        if ok == 0:
            for y in range(n):
                if graf[x][y] and viz[y] == 0:
                    tata[y] = x
                    DF(y)
                    if ok == 1:
                        return
                elif y != tata[x]:
                    print("ciclu elementar")
                    v = x
                    while v != y:
                        afisare.append(v)
                        nr+=1
                        v = tata[v]
                    afisare.append(y)
                    afisare.append(x)
                    if nr%2==1:
                        return
                    else:
                        afisare=[]
                        nr=1
    DF(0)
    print("ciclul este: ", afisare )
    print("lungimea lui este: ", nr)
print("vectorul de culori: ", culoare[1:])
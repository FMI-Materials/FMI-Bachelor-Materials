'''
    Sortare topologica var 1
    folosind BF si o lista cu gradele interne ale nodurilor
    incep de la nodurile cu gradul intern 0
    graf orientat
    nu merge pe graf cu circuite
'''
f = open("fisier.in")
n = f.readline()
n = int(n)
line = f.readline()
durata = [int(x) for x in line.split()]
m = f.readline()
m = int(m)
la = dict()
for i in range(m):
    line = f.readline()
    v = line.split()
    x = int(v[0])
    y = int(v[1])
    cost = durata[x - 1]
    if x in la.keys():
        la[x].append((y, cost))
    else:
        la[x] = [(y, cost)]

grad_intern = [0] * (n+1)
for key in la.keys():
    for nod, cost in la[key]:
        grad_intern[nod] = grad_intern[nod] + 1

for nod in range(1,n + 1):
    if grad_intern[nod] == 0:
        if n + 1 in la.keys():
            la[n+1].append((nod, 0))
        else:
            la[n+1] = [(nod, 0)]
    if nod not in la.keys():
        if n + 2 in la.keys():
            la[nod].append((n+2, durata[nod - 1]))
        else:
            la[nod] = [(n+2, durata[nod - 1])]

print(la)
n = n + 2
def sortare_topologica():
    #calculez gradul intern pt fiecare varf
    #de cate ori apare un nod in liste
    grad_intern = [0] * (n + 1)
    for key in la.keys():
        for nod, cost in la[key]:
            grad_intern[nod] = grad_intern[nod] + 1
        #alg de sortare topologica
    sortate = []
    from collections import deque
    c = deque([])
    #adaug in coada nodurule care au gradul 0
    for i in range(1, n+1):
        if grad_intern[i] == 0:
            c.append(i)
    nod = 0
    while len(c) > 0:
        i = c.popleft()
        sortate.append(i)
        if i in la.keys():
            for j, cost in la[i]: #pt fiecare muchie de la i la j
                nod = j
                grad_intern[j] = grad_intern[j]-1 #scad gradul
                if grad_intern[j] == 0: #daca e 0 il adaug in coada si pe el
                    c.append(j)
    #detectare nod in care incepe si se termina un circuit
    #nodul la care se blocheaza
    if len(sortate) != n:
        print ("graf cu circuit \nnodul la care avem circuit: ", nod)
    else:
        print(*sortate)
    return sortate


def DAG_maxim(s, t):
    sortate = sortare_topologica()
    dist = [-float("inf") for i in range(n+1)]
    dist[s] = 0
    tata = [0 for i in range(n+1)]
    for i in sortate:
        if i in la.keys():
            for j, cost in la[i]:
                if dist[j] < dist[i] + cost:
                    dist[j] = dist[i] + cost
                    tata[j] = i
    print(dist)
    print(dist[t])
    poz = tata[t]
    print("activitati critice: ")
    while poz != s:
        print(poz)
        poz = tata[poz]
    for i in range (1, n-1):
        print(f"{i}: {dist[i]} {dist[i] + durata[i-1]}")
DAG_maxim(n-1, n)


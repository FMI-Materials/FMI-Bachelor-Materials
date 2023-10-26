# # Algoritm pentru calcularea fluxului.
# from queue import Queue
#
# f = open("flux.in")
# line = f.readline()
# v = line.split()
# n = int(v[0])
# m = int(v[1])
#
# noduri_intrare = [[] for i in range(n + 1)]
# noduri_iesire = [[] for i in range(n + 1)]
# cost = [[0 for j in range(n + 1)] for i in range(n + 1)]
# flux = [[0 for j in range(n + 1)] for i in range(n + 1)]
# tata = [0] * (n + 1)
#
# for i in range(m):
#     line = f.readline()
#     v = line.split()
#     x = v[0]
#     y = v[1]
#     if x == 's':
#         x = 0
#     elif x == 't':
#         x = n - 1
#     else:
#         x = int(x)
#
#     if y == 's':
#         y = 0
#     elif y == 't':
#         y = n - 1
#     else:
#         y = int(y)
#
#     c = int(v[2])
#     noduri_iesire[x].append(y)
#     noduri_intrare[y].append(x)
#     cost[x][y] = c
#
# f.close()
#
#
# def lant_nesaturat_BFS(s, t):
#     vizitat = [0] * (n + 1)
#     coada = Queue(maxsize = n + 1)
#     coada.put(s)
#     vizitat[s] = 1
#     while not coada.empty():
#         nod = coada.get()
#         for i in noduri_iesire[nod]:
#             if vizitat[i] == 0 and cost[nod][i] - flux[nod][i]:
#                 coada.put(i)
#                 vizitat[i] = 1
#                 tata[i] = nod
#                 if i == t:
#                     return True
#
#         for i in noduri_intrare[nod]:
#             if vizitat[i] == 0 and flux[nod][i] > 0:
#                 coada.put(i)
#                 vizitat[i] = 1
#                 tata[i] = (-1) * nod
#                 if i == nod:
#                     return True
#     return False
#
#
# def EdmondKarp(s, t):
#     global tata
#     index = 1
#     while lant_nesaturat_BFS(s, t):
#         x = t
#         initial = float("infinity")
#         while x != s:
#             if tata[x] >= 0:
#                 initial = min(initial, cost[tata[x]][x] - flux[tata[x]][x])
#             else:
#                 initial = min(initial, flux[x][-tata[x]])
#             x = abs(tata[x])
#
#         while x != s:
#             if tata[x] >= 0:
#                 flux[tata[x]][x] += initial
#             else:
#                 flux[x][-tata[x]] -= initial
#             x = abs(tata[x])
#         index += 1
#     for linie in flux:
#         print(*linie)
#
#
# EdmondKarp(0, n - 1)



from queue import Queue
file = open('flux.in', 'r')

def citire():
    line = file.readline().split()
    n = int(line[0])
    muchii = int(line[1])
    lista_intrare=[[] for i in range(n)]
    lista_iesire=[[] for i in range(n)]
    f=[[ 0 for j in range(n) ] for i in range(n)]
    c=[[0 for j in range(n)] for i in range(n)]
    for i in range(muchii):
        line = file.readline().split()
        nod1=line[0] #nodul 1
        nod2=line[1] #nodul 2
        if nod1 == "s":
            nod1=0
        if nod1 == "t":
            nod1 == n-1
        if nod2 == "s":
            nod2=0
        if nod2 == "t":
            nod2=n-1
        nod1=int(nod1)
        nod2=int(nod2)
        cost=int(line[2]) #costul muchiei
        lista_iesire[nod1].append(nod2)
        lista_intrare[nod2].append(nod1)
        c[nod1][nod2]=cost
    return lista_intrare,lista_iesire,n,muchii,f,c

def construieste_s_t_lant_nesaturat_BF(s,t):
    print("noul bfs",s)
    for index in range(0,n):
        vizitat[index]=0
        tata[index]=0
    queue = Queue(maxsize=n)
    queue.put(s)
    vizitat[s]=1
    #print(f)
    while queue.empty() == False:
        i = queue.get()
        print(i)
        #arc direct
        for j in lista_iesire[i]: #arce ij - care ies din i
            if vizitat[j]==0 and c[i][j]-f[i][j]:
                queue.put(j)
                vizitat[j]=1
                tata[j]=i
                if j == t:
                    return True
        #arc invers
        for j in lista_intrare[i]:
            if vizitat[j] == 0 and f[i][j]>0:
                queue.put(j)
                vizitat[j]=1
                tata[j]=(-1)*i
                if j == t:
                    return True
    return False

def edmonds_karp(s,t):
    #fluxul este nul
    #construieste_s_t_lant_nesaturat_BF(s,t)
    #print(tata)
    index=1
    while construieste_s_t_lant_nesaturat_BF(s,t):
        #revizuim fluxul
        x=t
        ip=float("inf")
        while x != s:
            if tata[x]>=0:
                #tata[x],x -capac lui reziduala c[tata[x]][x]-f[tata[x]][x]
                ip=min(ip,c[tata[x]][x]-f[tata[x]][x])
            else:
                #x,-tata[x] capac rezid f[x][-tata[x]]
                ip=min(ip,f[x][-tata[x]])
            x=abs(tata[x])
        print(f"Ip la pasul {index} este : {ip}")
        #print(tata)
        x=t
        while x != s:
            if tata[x]>=0:
                f[tata[x]][x]+=ip
            else:
                f[x][-tata[x]]-=ip
            x=abs(tata[x])
        index = index + 1
        #print(f)
    for linie in f:
        print(*linie)

lista_intrare,lista_iesire,n,muchii,f,c  = citire() #grafuri orientate
#print(lista)
#print(f)
vizitat=[0 for i in range(n+1)]
tata=[None for i in range(n+1)]


#FLUXURI
#ALGORITMUL LUI EDMONDS-KARP

edmonds_karp(0,n-1)

file.close()



out = open('graf.out', 'w')
out.close()
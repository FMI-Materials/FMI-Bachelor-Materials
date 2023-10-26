import heapq
ls=[[5,7],[1,3],[1,6],[7,8]]
ls.sort()
sali=[] #vectorul de sali sali[0]= lista intervalelor din sala 1
h=[]
pa=ls[0] #primul interval
sali.append([pa])
heapq.heappush(h,(pa[1],0)) #(terminarea primei activ, sala 0)

for i in range(1,len(ls)):
    ac=ls[i] #intervalul curent
    timp_term,nr_sala=heapq.heappop(h) #sala cu timpul de terminare cel mic
    if ac[0]>timp_term: #se poate adauga in sala
        sali[nr_sala].append(ac)
        heapq.heappush(h,(ac[1],nr_sala)) #sala nr_sala se termina acum la momentul ac[1]
    else:
        heapq.heappush(h,(timp_term,nr_sala)) #nu am folosit sala -o reinserez in heap cum era
        sali.append([ac]) #sala noua doar cu activ ac
        heapq.heappush(h,(ac[1],len(sali)-1)) #adaugam in heap
for sala in sali:
    print(*sala)

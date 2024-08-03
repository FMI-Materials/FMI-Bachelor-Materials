import heapq
f=open("activitati.in")
n=int(f.readline())
ls_activitati=[]
for i in range(1,n+1):
    ls = f.readline().split()
    t= (int(ls[0]) , int(ls[1]) ,i)
    ls_activitati.append(t) #deadline, profit, indicele
print(ls_activitati)  
#ordonam descrescator dupa termen limita pt a le putea insera in heap pe rand, descrescator dupa termen

ls_activitati.sort(reverse=True)
h=[]
planificari=[-1 for i in range(n)] #axa timpului
i=0
for t in range(n,0,-1): #
    #inseram in heap activitatile cu termenul limita t
    #heapul trebuie sa fie max-heap dupa profit, deci inseram perechi de forma (-profit,indice)
    while (i<len(ls_activitati)) and ls_activitati[i][0]==t:
        a=ls_activitati[i] #deadline, profit, indicele
        heapq.heappush(h,(-a[1],a[2])) #(-profit,indice)
        i+=1
    #la pasul t- programam activ cu profit maxim dintre cele din heap (celel cu termen>=t)
    if len(h)>0:
        a=heapq.heappop(h) #activitatea cu profitul cel mai mare (-profit,indice)
        planificari[t-1]=a[1]
print(planificari)

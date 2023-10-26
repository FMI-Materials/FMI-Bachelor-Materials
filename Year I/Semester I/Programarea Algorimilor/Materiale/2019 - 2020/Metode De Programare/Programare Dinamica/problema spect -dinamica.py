# ora_st ora_fin profit
n=6 #int(input())
l=list()
profit=list()
f=open("descompunere.in")
planificare=[]
for i in range(n):
   planificare.append([]) #folosita pentru afisare
for i in range(n):
    sir=f.readline().split()
    l.append(sir)
for i in range(len(l)):
    profit.append(int(l[i][2]))
    l[i].pop()
#in urma a tot ce e aici putem spune ca avem:
#lista l in care se afla ora de start si de finala (cand le bagi in fisier, vezi sa fie deja sortate dupa ora de final :D)
#profit in care se afla profiturile fiecarei activitati
lista_profite=profit.copy() #asta este lista de profituri pe care o sa o mai modific cand actualizez profitul pana la un eveniment
i=0
for i in range(len(l)): #aici am convertit ora de start si de final din string in int,nu ma intreba de ce n am facut direct mai sus :)))
    l[i][0]=int(l[i][0])
    l[i][1]=int(l[i][1])
i=0
while i<=len(l)-1:
    for j in range(i,-1,-1):
        if l[i][0]>=l[j][1]: #aici fac chestia cu i si j facuta de indian (ai linkul mai jos)
            if profit[i]+lista_profite[j]>lista_profite[i]:
                lista_profite[i]=profit[i]+lista_profite[j]
                planificare[i].append(j)
#probabil te intrebi care e faza cu planificare asta...in el o sa retin
#indicii evenimentelor care alcatuiesc profitul evenimentului curent (o sa te lamuresti dupa ce te uiti la indian)
    while  i!=len(l)-1 and l[i][1]<=l[i+1][0]:
#in acest while practic sar direct de la un eveniment la altul daca se poate
#de ex daca am (2,3) si (4,5) se va duce direct la el iar daca am (2,3) si (3,5) nu va intra in while
            lista_profite[i+1]+=lista_profite[i]
            planificare[i].append(i)
            i+=1
    if i==len(l)-1:
#fac procesul cu i si j separat pentru ultimul eveniment
        for j in range(i, -1, -1):
            if l[i][0] >= l[j][1]:
                if profit[i] + lista_profite[j] > lista_profite[i]:
                    lista_profite[i] = profit[i] + lista_profite[j]
                    planificare[i].append(j)
    i+=1
print(lista_profite)
print(planificare)
#cautare pozitie profit maxim
i=-1
indice=0
max=0
for x in lista_profite:
    i+=1
    if max<x:
        max=x
        indice=i
#in forul de mai sus am retinut profitul maxim si indicele sau
planificare_afisare=list() #aceasta lista reprezinta afisarea necesara
planificare_afisare.append(l[indice])
while planificare[indice]!=[]:
#si aici e o carpeala facuta de mine ca sa afiseze restul de activitati
#trebuia ceva recursiv
#de exemolu tie pe ecran iti afiseaza pe prima linie lista de profituri modificate
#pe a 2 a liniee chestia cu planificare si toata treaba functioneaza in felul urmator:
#profitul maxim este 17 care are indicele 4, o sa il adaug la planificare afisare
#apoi ma uit in planificare (linia 2 de la afisare) pe pozitia 4 unde se afla 1,ceea ce inseamna ca voi
#afisa si activitatea ce are indicele 1
#apoi verific in continuare daca in planificare de 1 se afla ceva si nu se va afla (pe ex asta)
#Observatie!!!!!!
#la problema asta am luat intervalele ca fiind inchise iar proful le a luat deschise
    for x in planificare[indice]:
        planificare_afisare.append(l[x])
    indice=planificare[indice][0]

print(planificare_afisare)
#link problema de la indian: https://www.youtube.com/watch?v=cr6Ip0J9izc&t=6s
"""
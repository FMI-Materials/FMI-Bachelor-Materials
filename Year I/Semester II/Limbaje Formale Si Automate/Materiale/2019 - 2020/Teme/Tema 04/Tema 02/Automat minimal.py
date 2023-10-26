f=open("in2.txt")
stari=int(f.readline()) #numarul total de stari
#initial=int(f.readline()) #starea initiala pp ca e 0
nrf=int(f.readline()) #numar de stari finale
finale=[] #starile finale
for i in range(nrf):
    finale.append(ord(f.readline().strip('\n'))-97)
nrtranz=int(f.readline()) #nr tranzitii
m=[] #matricea grafului
for i in range (stari):
    M=[]
    for j in range (stari):
        M.append([])
    m.append(M)
for i in range(nrtranz): #citire tranzitii
    x=f.readline()
    x=x.strip('\n')
    v=x.split()
    a=ord(v[0])-97
    b=ord(v[1])-97
    cifra=int(v[2])
    m[a][b].append(cifra)

f.close()
print("matricea grafului este:")
for i in range (stari):
    print (m[i])
#folosesc Myhill Nerode Theorem

#pasul 1
#am nevoie de jumatatea de tabel
#creare jumatate de tabel
T=[]
for i in range (stari):
    t=[]
    for j in range(i):
        t.append([])
    T.append(t)
#pasul 2
#completare tabel
for i in range (1,stari):
    for j in range(i):
        if i in finale and j not in finale:
            T[i][j].append(1)
        elif i not in finale and j in finale:
            T[i][j].append(1)
        else:
            T[i][j].append(0)

#pasul 3
#iau la verificat perechile nemarcate
# verific daca drumurile lor alcatuiesc alta pereche marcata
#=> le marchez si pe ele
# repet pana cand nu mai am ce marca(marcat ramane 0)
marcat=1
while marcat==1:
    marcat=0
    for i in range (1,stari):
        for j in range(i):
            #print("a=",i,"b=",j, sep=' ')

            if T[i][j]==[0]: #nu e marcat
                #cazul cu 0
                 gasit1=-1
                 gasit2=-1

                 for x in range(stari) :
                     if m[i][x]==[0] or 0 in m[i][x]:
                        gasit1=x
                        break
                 for x in range(stari):
                     if m[j][x] == [0] or 0 in m[j][x]:
                        gasit2 = x
                        break

                # print("a cu 0: ", gasit1,"b cu 0: ", gasit2, sep=' ')
                # if gasit1>-1 and gasit2 >-1 and gasit1>gasit2 and (T[gasit1][gasit2]==[1] or T[gasit2][gasit1]==[1]):
                 if gasit1>-1 and gasit2 >-1 and gasit1!=gasit2 :
                     if gasit1>gasit2 and T[gasit1][gasit2]==[1]:
                         #plus conditia sa fie sub DP
                         #marchez
                         T[i][j][0]=1
                         marcat=1
                     elif gasit1<gasit2 and T[gasit2][gasit1]==[1]:
                         # plus conditia sa fie sub DP
                         # marchez
                         T[i][j][0] = 1
                         marcat = 1

                 # cazul cu 1
                 gasit11 = -1
                 gasit22 = -1
                 for x in range(stari):
                     if m[i][x] == [1] or 1 in m[i][x]:
                         gasit11 = x
                         break
                 for x in range(stari):
                     if m[j][x] == [1] or 1 in m[j][x]:
                         gasit22 = x
                         break
                # print("a cu 1: ", gasit11, "b cu 1: ", gasit22, sep=' ')
                 if gasit11 > -1 and gasit22 > -1 and gasit11 != gasit22:
                    if gasit11 > gasit22 and T[gasit11][gasit22] == [1]:
                        # plus conditia sa fie sub DP
                        # marchez
                        T[i][j][0] = 1
                        marcat = 1
                    elif gasit11 < gasit22 and T[gasit22][gasit11] == [1]:
                        # plus conditia sa fie sub DP
                        # marchez
                        T[i][j][0] = 1
                        marcat = 1
                 #if gasit11 > -1 and gasit22 > -1 and gasit11 > gasit22 and (T[gasit11][gasit22]==[1] or T[gasit22][gasit11]==[1]):
                         # plus conditia sa fie sub DP
                         # marchez
                    # T[i][j][0] = 1
                    # marcat = 1



#pt afisat
print("Tabel T:")
for i in range (1,stari):
    print (T[i])
#pasul 4 alcatuiesc noul AFD
#iau perechile nemarcate din tabel
#vector pentru impartire pe componente
v=[]
for i in range(stari):
    v.append(0)
comp=1
#lista de tupleturi cu perechile
list=[]
for i in range (1,stari):
    for j in range(i):
        if T[i][j]==[0]: #nu e marcat
            if v[i]==0 and v[j]==0:
                v[i]=v[j]=comp
                comp+=1
            elif v[i]!=0 and v[j]==0:
                v[j]=v[i]
            elif v[i]==0 and v[j]!=0:
                v[i]=v[j]
            list.append((chr(97+i),chr(97+j)))

#am impartit pe componente
componente=[]
for i in range(comp):
        ok=0
        for j in range(stari):
            if v[j]==i:
                if i==0:
                    componente.append([j])
                else:
                   if ok==0:
                        componente.append([j])
                        ok=1
                   else:
                        componente[-1].append(j)

componente.sort() # ca sa ajunga starea initiala prima
print("componentele sunt:")
print(componente)

#fac o lista si cu componentele finale
cfinale=[]
for x in componente:
    for c in x:
        if c in finale:
            cfinale.append(x)
            break

print("componentele finale sunt:")
print(cfinale)

#transform matricea m intr-o matrice a unui graf orientat
drumuri=[]
for i in range(stari):
    d=[]
    drumuri.append(d)
for i in range(stari):
    for j in range(stari):
        if len(m[i][j])!=0:
            drumuri[i].append(1)
        else:
            drumuri[i].append(0)

#roy warshall=> matricea drumurilor
# daca avem circuit pe dp principala pune 1
for k in range(stari):
    for i in range(stari):
        for j in range(stari):
            if i!=k and j!=k and drumuri[i][j]==0:
                drumuri[i][j]=drumuri[i][k]*drumuri[k][j]

elimin=[]#lista cu ce noduri trebuie eliminate
#trebuie sa elimin drumurile care nu duc la stari finale
#deci scot nodurile din care plec si nu ajung in stari finale
for f in finale :
        for i in range(stari):
            if i!=f and drumuri[i][f]==0:
                if i not in elimin:
                    elimin.append(i)
print ("trebuie sa elimin nodurile:")
print(elimin)
print("componentele dupa eliminare sunt:")
if len(elimin)!=0:
    comp_inainte=componente.copy()
    componente.clear()
    for e in elimin:
        for x in comp_inainte:
            if e not in x and x not in componente:
                componente.append(x)
print(componente)

comp_l=[]
for x in componente:
    s=""
    for y in x:
        s=s+chr(y+97)
    comp_l.append(s)
print("componentele in litere sunt:")
print(comp_l)
#indicii vectorului sunt numarul componentelor
#lista de muchii corespunzatoare componentelor
muchii={}
#adaug intai muchiile interne cu componentele din care fac parte
#muchiile care sunt catre ele insasi
for i in range (len(componente)):
    muchii[(i,i)]=[]

for i in range (len(componente)):
    l=componente[i].copy()
    if len(l)==1:
        if len(m[l[0]][l[0]]) != 0:
            if m[l[0]][l[0]] not in muchii[(i,i)]:
                muchii[(i,i)].append(m[l[0]][l[0]])

    for j in range (len(l)-1):
       if len(m[l[j]][l[j+1]])!=0:
           if m[l[j]][l[j+1]] not in muchii[(i,i)]:
                muchii[(i,i)].append(m[l[j]][l[j+1]])

       if len(m[l[j+1]][l[j]]):
           if m[l[j+1]][l[j]] not in muchii[(i,i)]:
                muchii[(i,i)].append(m[l[j+1]][l[j]])
#acum pun muchiile de legatura
#for de sortare
for I in range(len(componente)):
    c=componente[I].copy()

    for J in range (I+1,len(componente)):
        C=componente[J].copy()
        #caut sa vad daca exista muchii de la c la C

        for i in c:
            for j in C:

                if len(m[i][j])!=0:
                    if (I,J) not in muchii.keys():
                        muchii[(I,J)]=[]
                        muchii[(I,J)].append(m[i][j])
                    else:
                        if m[i][j] not in muchii[(I,J)]:
                            muchii[(I,J)].append(m[i][j])
                    #trebuie luate si invers
                if len(m[j][i]) != 0:
                    if (J, I) not in muchii.keys():
                        muchii[(J, I)] = []
                        muchii[(J, I)].append(m[j][i])
                    else:
                        if m[j][i] not in muchii[(J, I)]:
                            muchii[(J, I)].append(m[j][i])


print("dictionarul cu muchii este:")
print(muchii)
print("AFN minimal:")
for k in muchii.keys():
    a=k[0]
    b=k[1]
    for x in muchii[k]:
        for t in x:
            print(comp_l[a], comp_l[b], t, sep=' ')





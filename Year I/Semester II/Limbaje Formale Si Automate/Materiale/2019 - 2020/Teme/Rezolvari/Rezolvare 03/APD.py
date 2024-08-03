f=open("in.txt")
#lucrez de la 0
#pt efsilon am simbolul $

#nr stari
#nr stari finale
#stari finale
#nr tranzitii
#tranzitii:
#            nod1-nod2:litera,partea1(cu spatii)/parte2(cu spatii) ex:1,z0/1 z0
#               !!! la citire la partea 2 le bag invers
#cuvantul ai grija sa-i pui $ si la inceput si la sfarsit!!!
n=int(f.readline())#nr stari
nrf=int(f.readline())#nr stari finale
finale=[]
for i in range (nrf):#starile finale
    x=int(f.readline())
    finale.append(x)
trz=int(f.readline()) #nr tranzitii
tranzitii={}
for i in range(trz):
    #nod1-nod2:litera,partea1(cu spatii)/parte2(cu spatii) ex:1,z0/1 z0
    s = f.readline()
    v=s.split(',')
    if v[0] not in tranzitii.keys():
        tranzitii[v[0]]=[]
    x=v[1].split('/')
    a=x[0].split()
    b=x[1].split()
    tranzitii[v[0]].append([a,b])
#print("dictionarul cu tranzitii")
#for k in tranzitii.keys():
    #print(k,":",tranzitii[k])
#cuvant
cuvant=f.readline()
f.close()
stiva=['z0']

def parcurg(x, cuv):         #functie recursiva parcurgere in adancime
    global ok, stiva
    copie = cuv
    for i in range(n):
            if ok == 1:
                return
            l = [chr(x + 48), chr(i + 48)]
            s = "-".join(l)
            s = s + ":" + cuv[0]
            if s in tranzitii.keys():
                v = tranzitii[s]
                for vect in v:
                    if ok == 1:
                        return
                    if vect[0][0] == stiva[-1]:
                        cuv=cuv[1:] #sterg primul caracter
                        stiva.pop()
                        for m in vect[1]:
                            if m != '$':
                                stiva.append(m)

                        #print(cuv)
                        #print(stiva)


                        if len(cuv) == 0:
                            if i not in finale and len(stiva) == 1 and stiva[0] == 'z0':
                                cuv=cuv+'$'
                        if len(cuv) == 0:
                            #if i in finale and len(stiva) == 1 and stiva[0] == 'z0':
                            if i in finale and len(stiva) == 0 :
                                ok = 1
                            return
                        parcurg(i, cuv)
                        cuv = copie


if cuvant=='$' and 0 in finale: #tratez cazul in care avem cuvantul vid
    print("cuvantul dat este acceptat")
else:
    ok = 0
    print("cuvantul este:", cuvant, sep=" ")
    parcurg(0, cuvant)
    if ok==0:
        print("NU este acceptat")
    else:
        print("acceptat")


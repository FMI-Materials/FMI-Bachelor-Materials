f=open("in.txt")
# am folosit '$' pentru simbolizarea cuvantului vid
stari=int(f.readline()) #numarul total de stari
initial=int(f.readline()) #starea initiala
nrf=int(f.readline()) #numar de stari finale
finale=[] #starile finale
for i in range(nrf):
    finale.append(int(f.readline()))
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
    a=int(v[0])
    b=int(v[1])
    litera=v[2]
    m[a][b].append(litera)
cuvant=f.readline() # citire cuvant

f.close()
def parcurg(x, cuv):         #functie recursiva parcurgere in adancime
    global ok
    copie = cuv
    for i in range(stari):
        if len(m[x][i])!=0 and ( cuv[0] in m[x][i]) :
            cuv=cuv[1:] #sterg primul caracter
            if len(cuv)==0:
                if i in finale:
                    ok=1
                return
            #print(x,i)
            #print(cuv)
            parcurg(i, cuv)
            cuv = copie

if cuvant=='$' and initial in finale: #tratez cazul in care avem cuvantul vid
    print("cuvantul dat este acceptat")
else:
    ok = 0
    parcurg(initial, cuvant)
    if ok==0:
        print("cuvantul dat nu este acceptat")
    else:
        print("cuvantul dat este acceptat")
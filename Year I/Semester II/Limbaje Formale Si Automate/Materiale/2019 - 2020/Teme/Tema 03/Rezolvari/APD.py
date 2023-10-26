f=open("automat.in","r")

cuv=f.readline()
stin=int(f.readline())
nrstfin=int(f.readline())
stfin=[]
for x in f.readline().split():
    stfin.append(int(x))
nrtran=f.readline()
tran=[]
for i in range(100):
    tran.append([])
for i in range(int(nrtran)):
    aux=f.readline().split(" ",1)
    aux[1]=aux[1][0:len(aux[1])-1]
    tran[int(aux[0])].append(aux[1].split())
st=['Z']
q=[(st,stin)]   #tuple stiva actuala, starea actuala
ql=list()   #coada de litere
ql.append(stin) #incep cu starea init
start=0
last=len(q)
posib=list()

while(start!=last):
    o=q[start]  #el. actual din stiva
    nst=o[0]    #noua stiva
    litera=cuv[ql[start]] #litera cu care plec din cuvant
    if litera=='\n':    #daca s-a terminat cuvantul, pot adauga o posibila solutie
        posib.append([int(o[1]), nst])
    for x in tran[int(o[1])]:   #se cauta o posibila urmatoare tranzitie
        if(x[1]==litera and nst[0]==x[2]):  #daca am gasit-o, o adaug in coada
            nst.pop(0)
            rg=0
            for lit in x[3]:
                if lit != '.':
                    nst.insert(rg,lit)
                    rg+=1
            ql.append(ql[start]+1)
            q.append((nst,x[0]))
            last+=1
    start+=1
ok=False
for x in posib:
    if ok==True:
        break
    for y in tran[x[0]]:
        if(x[1][0]=='Z' and y[2]=='Z'):
            if(int (y[0]) in stfin):
                ok=True
                print("Cuvant acceptat")
                break
if(ok==False):
    print("Cuvant neacceptat")





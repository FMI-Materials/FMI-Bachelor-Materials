f=open("graf.txt","r")
cuv=f.readline()
cuv=cuv.strip('\n')
n=int(f.readline())
m=int(f.readline())

'''
for i in range(m):
    line=f.readline()
    line=line.strip("\n")
    x=line.split()
    l.append((int(x[0]), int(x[1])))
 
 '''
d={}
for i in range(m):
    line = f.readline()
    line = line.strip("\n")
    x = line.split()
    a=int(x[0])
    b=int(x[1])
    if a in d:
        d[a].append(b)

    else:
        d[a]=[]
        d[a].append(b)
    if b in d:
            d[b].append(a)

    else:
            d[b] = []
            d[b].append(a)

'''
a=[None]*(n+1)
for i in range(n):
    a[i+1]=[0]*(n+1)
for i in range(m):
    line = f.readline()
    line=line.strip('\n')
    l = line.split()
    i=int(l[0])
    j=int(l[1])
    a[i][j]=a[j][i]=1

for i in range(n):
    print(a[i+1][1:])
'''

plec=int(f.readline())
ajung=int(f.readline())
f.close()

bf=[]
bf.append((plec,-1))
st=dr=0
while st<=dr:
    tata=bf[st][0]
    for fiul in d[tata]:
        if fiul not in [nod for (nod,parinte) in bf]:
            bf.append((fiul,tata))
            dr+=1
    st+=1
#for x in bf:
    #print(x[0])


'''
df=[]
vizitat=[]
df.append(plec)
vizitat.append(plec)
while df !=[]:
    tata=df[-1]
    for fiul in d[tata]:
        if fiul not in vizitat:

             df.append(fiul)
             vizitat.append(fiul)
             break
        else:
             df.pop(-1)
for x in vizitat:
    print(x)
'''

tata=ajung
afis=[ajung]
while tata!=plec:

     for a in bf:
        if a[0]==tata:
                tata=a[1]
                break
     afis.append(tata)
afis.reverse()
if len(afis)==0:
    print("nu exista drum")
else:
    print(*afis)

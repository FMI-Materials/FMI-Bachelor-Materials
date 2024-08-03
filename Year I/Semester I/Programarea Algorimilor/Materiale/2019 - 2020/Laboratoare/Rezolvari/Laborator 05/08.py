f=open ("proiecte.txt","r")
l=[]
for line in f:
   v=line.split()
   l.append((v[0], int(v[1]), int(v[2])))
T=1
d={}
L = sorted(l, reverse=True, key=lambda x: x[0])
for x in  L:
    if x[1] in d:
        d[x[1]].append((x[0],x[2]))
    else:
        d[x[1]]=[]
        d[x[1]].append((x[0],x[2]))
T=L[0][1]
s=0
s+=L[0][2]
ok=True
while ok==True:





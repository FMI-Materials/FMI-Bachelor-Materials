f=open("spectacolee.txt","r")
l=[]
for line in f:
    line=line.strip("\n")
    v=line.split(" ",1)
    x=v[0].split("-")
    l.append((x[0],x[1],v[1]))
l=sorted(l,key=lambda x: x[0])
print(l)
d={}
k=1
d[k]=[]
d[k].append(l[0])

for i in range(1,len(l)):
    ok=False
    for j in range(1,k+1):
        x=d[j].copy()
        t=d[j][len(x)-1]
        if l[i][0]>=t[1]:
            d[j].append(l[i])
            ok=True
            break
    if ok==False:
        k+=1
        d[k]=[]
        d[k].append(l[i])
print(k)
print(d)


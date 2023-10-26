a=[(1,2),(2,5),(9,10),(5,7)]
l=sorted(a,key=lambda x: x[0])
k=1
d={k: [l[0]]}

for i in range(1,len(l)):

    I=l[i]
    ok=False
    for i in range(1,k+1):
        x=d[i]
        if I[0]>x[-1][1]:
            d[i].append(I)
            ok=True
            break
    if ok==False:
        k+=1
        d[k]=[]
        d[k].append(I)
print(d)

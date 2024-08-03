f=open("spectacole.txt","r")
l=[]
for line in f:
    v=line.split(" ",1)
    x=v[0].split("-")
    l.append((x[0],x[1],v[1]))
f.close()
l=sorted(l,key=lambda x: x[1])
sol=[l[0]]
k=0
for i in range(1,len(l)):
    if sol[k][1]<l[i][0]:
        sol.append(l[i])
        k+=1
print(sol)

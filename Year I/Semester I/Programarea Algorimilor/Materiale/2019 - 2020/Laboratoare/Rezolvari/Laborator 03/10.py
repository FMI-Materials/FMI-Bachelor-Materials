f=open("inventar.txt","r")
d={}
for x in f:
   l=x.split()
   d[l[0]]=set()
   for i in range(1,len(l)):
       d[l[0]].add(int(l[i],10))
nou=d[l[0]] #ultimul magazin
for x in d :
    nou=nou & d[x]
print(*nou, sep=" ")
n=set() #ultimul magazin
for x in d :
    n=n | d[x]
print(*n, sep=" ")
for x in d:
    a=d[x]
    for y in d:
        if y!=x:
            a=a-d[y]
    print(x,*a,sep=" ")
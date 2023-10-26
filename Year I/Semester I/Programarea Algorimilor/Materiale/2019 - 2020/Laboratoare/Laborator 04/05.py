def negative_pozitive (l):
    n=[]
    p=[]
    for x in l:
        if x<0:
            n.append(x)
        elif x>0:
            p.append(x)
    return n,p
nume=input()
f=open(nume,"w")
l=[1,0,-2,3,4,-9,4,-10]
n,p=negative_pozitive(l)
n.sort()
p.sort()
N=""
P=""
for x in n:
    N+=str(x)+" "
for x in p:
    P+=str(x)+" "
f.write(N+'\n'+P)
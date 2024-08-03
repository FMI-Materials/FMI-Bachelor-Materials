def citire():
    n=int(input())
    l=[]
    for i in range(n):
        x=int(input())
        l.append(x)
    return n,l
def b(l,i,j,x):
    for a in range(i,j+1):
        if l[a]>x:
            return a
    return -1
n,l=citire()
ok=True
l.reverse()
for i in range(n-1):
    if b(l,i,i+1,l[i])!=i+1:
        ok=False
        break
if ok==True:
    print("da")
else:
    print("nu")


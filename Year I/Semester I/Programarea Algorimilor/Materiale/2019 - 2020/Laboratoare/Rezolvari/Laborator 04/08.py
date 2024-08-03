f=open("angajati.txt","r")
l=[]
for line in f:
    line=line.strip("\n")
    v=line.split(",")
    l.append((v[0],int(v[1]),int(v[2])))
f.close()
nume=input()
def a(l):
    for x in l:
        if nume==x[0]:
            print(*x)
            break
a(l)
def b(l):
    max=0
    for x in l:
        if x[2]>max:
            max=x[2]
    print(max)
    for x in l:
        if x[2]==max:
            print(x[0])
b(l)
def c(l):
    nr=len(l)
    s=0
    for x in l:
        s+=x[2]
    print(s/nr)
c(l)
L=sorted(l,reverse=True,key=lambda x: x[1]  )
print(L)
ll=sorted(L,key=lambda x: x[0])
print(ll)
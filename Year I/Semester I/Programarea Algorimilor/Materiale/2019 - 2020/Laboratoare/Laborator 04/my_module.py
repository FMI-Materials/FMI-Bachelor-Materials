def citire():
    n=int(input())
    v=[]
    for i in range(n):
        x=int(input())
        v.append(x)
    return n,v
def afisare(v):

        print(*v, sep=" ")
def valpoz (v):
    p=[]
    for x in v:
        if x>=0:
            p.append(x)

    return p
def semn(v,n):
    for i in range(n):
        v[i]=v[i]*-1


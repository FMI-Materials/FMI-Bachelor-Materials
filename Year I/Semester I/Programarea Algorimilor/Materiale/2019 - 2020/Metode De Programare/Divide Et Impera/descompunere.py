def dr(a,b):
    global d,n
    n1=0
    if b-a>=a or a==b:
        n=1
        d.append(a)
        d.append(b)
    if b-a< 2*a-b:
        dr(b-a, 2*a-b)
    else:
        dr (2*a-b, b-a)

    if a%2==0:
        if a<b-a/2:
            dr(a,b-a/2)
        else:
            dr(b-a/2,a)
    else:
        n2=nmax
    if n1<=n2:
        n=n1+n2
        d[0]=a
        d[1]=b-a


d=[]
nmax=n=7
dr(21,34)



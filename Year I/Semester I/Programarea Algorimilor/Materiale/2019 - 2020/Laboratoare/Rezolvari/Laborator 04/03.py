def min_max (*args):
    if len(args)>0:
        l=[]
        m=M=None
        for x in args:
            if int(x)==x:
                l.append(x)
        if len(l)>0:
            m=min(l)
            M=max(l)
        if m==None and M==None:
            return None
        else:
            return m,M
    else:
        return None
try:
    f=open("numere.txt","r")
    g=open("impartire.txt","w")
    x=f.readline()
    f.close()
    a=x.split()
    l=[]
    for i in a:
        l.append(int(i))
    m,M=min_max(*l)
    g.write(str(M/m))

except FileNotFoundError :
    print("fisierul nu exista")

except ZeroDivisionError :
    print("minimul este 0 ")

except Exception :
    print("nu s-au dat numere naturale")


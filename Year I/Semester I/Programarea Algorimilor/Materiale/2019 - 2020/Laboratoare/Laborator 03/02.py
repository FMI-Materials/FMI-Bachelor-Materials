f=open("test.in","r")
g=open("test.out","w")
nota=1
for x in f:
    x=x.strip("\n")
    l=x.split('=')
    v=l[0].split('*')
    rez=int(l[1],10)
    f1=int(v[0],10)
    f2=int(v[1],10)
    p=f1*f2
    if rez==p:
        nota+=1
        g.write(x+" corect"+'\n')
    else:
        g.write(x+" gresit "+str(p)+"\n")
g.write("Nota "+str(nota))
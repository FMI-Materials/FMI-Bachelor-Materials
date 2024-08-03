f=open("activitati.txt",'r')
n=int(f.readline())
l=[]
for i in range (n):
    line=f.readline()
    v=line.split()
    l.append((int(v[0]), int(v[1])))

l=sorted(l,key=lambda x: x[1])
si=0
sf=0
H=0
g=open("intarzieri.txt","w")
for i in range(0,len(l)):
    sf+=l[i][0]
    g.write(str(si)+"--->"+str(sf)+"    ")
    h=max(0,sf-l[i][1])
    g.write(str(l[i][1])+"     "+str(h)+"\n")

    if h>H:
        H=h
g.write(str(H))
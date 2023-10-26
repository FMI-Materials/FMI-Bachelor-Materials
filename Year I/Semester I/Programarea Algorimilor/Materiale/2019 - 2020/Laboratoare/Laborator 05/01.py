def afis_t_s(tis):
    s=0
    for i in range(len(tis)):
        ord=tis[i][0]
        serv=tis[i][1]
        if i==0:
            ast=tis[0][1]
        else:
            ast=ast+serv
        s+=ast
        print(ord,serv,ast,sep=" ")



    print(s/len(tis))
f=open("tis.txt","r")
s=f.readline()
l=[]
i=1
for x in s.split():
     l.append((i,int(x)))
     i+=1
afis_t_s(l)
print("dupa aranjare")

l=sorted(l,key=lambda x: x[1])
afis_t_s(l)
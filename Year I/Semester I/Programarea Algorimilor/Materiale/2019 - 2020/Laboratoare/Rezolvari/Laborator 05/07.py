f=open("obiecte.txt","r")
n=int(f.readline())
l=[]
for i in range(n):
    line=f.readline()
    v=line.split()
    l.append((int(v[0]), int (v[1]), int(v[0])/int(v[1])))
G=gr=int(f.readline())
f.close()
l=sorted(l, reverse=True, key=lambda x: x[2])
i=0
rc=[]
while gr>=l[i][1]:
    rc.append(l[i])
    gr-=l[i][1]
    i+=1
if gr!=0:
   p=gr/l[i][1]
print(p)
print(rc)


l=input()
v=[]
i=1
while l!='-1':
    x=l.find(" ")
    t=(int(l[:x]), l[x+1:], i)
    v.append(t)
    i+=1
    l=input()
s=set()
for x in v:
    s.add(x[0])
print(s)
l=sorted(s)
d={}
for x in v:
    if x[0] in d:
        d[x[0]].append((x[1],x[2]))
    else:
        d[x[0]]=[]
        d[x[0]].append((x[1], x[2]))
for x in d:
    d[x]=sorted(d[x], )
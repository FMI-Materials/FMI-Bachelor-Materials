p=input()
p=p.strip(".")
l=p.split()
d={}
for x in l:
    if x in d:
        d[x]+=1
    else:
        d[x]=1
D={}
for x in d:
    if d[x] in D:
        D[d[x]].append(x)
    else:
        D[d[x]]=[]
        D[d[x]].append(x)
m=min(D.keys())
M=max(D.keys())

print(min(D[m]))
print(min(D[M]))

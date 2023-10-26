v=[(2,5), (4,9), (5,6), (9,4), (4,3), (1,2), (3,2), (8,8)]
n=len(v)
l=[1]*n
lr=[1]*n
p=[-1]*n
pr=[-1]*n
for i in range(1,n):
    for j in range(i):
        if v[j][1]==v[i][0] and l[i]<l[j]+1:
            l[i]=l[j]+1
            p[i]=j
        if v[j][0]==v[i][0] and lr[i]<lr[j]+1:
            lr[i] = lr[j] + 1
            pr[i] = j
print(l,lr,p,pr)
m=max(l)
print(m)
poz=l.index(m)
afis=[]
while m>0:
    afis.append(v[poz])
    poz=p[poz]
    m-=1
afis.reverse()
print(afis)
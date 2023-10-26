#cel mai lung subsir crescator
v=[5,9,2,4,7,6,7,15,10,11,9]
n=len(v)
T=[1]*n
pred=[-1]*n
for i in range (1,n):
    for j in range(i):
        if v[i]>v[j] and T[i]<T[j]+1:
            T[i]=T[j]+1
            pred[i]=j
print(*T)
print(*pred)
m=max(T)
print(m)
poz=T.index(m)
afis=[]
while m>0:
    afis.append(v[poz])
    poz=pred[poz]
    m-=1
afis.reverse()
print(afis)
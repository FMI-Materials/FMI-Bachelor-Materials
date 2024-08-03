f=open("sir.in")
v=[int(x) for x in f.readline().split()]
f.close()
n=len(v)
lung=[0 for i in range(n)]
succ=[-1 for i in range(n)]
#lung[i] = lung max a unui subsir cresc care incepe pe pozitia i

lung[n-1]=1
succ[n-1]=-1

for i in range(n-2,-1,-1): #lung[i]=1+max{lung[j]|j>i si vj>vi}
    max_lung=0
    succ[i] = -1
    for j in range(i+1,n):
        if (v[j]>v[i]) and (lung[j]>max_lung):
            max_lung=lung[j]
            succ[i]=j
    lung[i] = 1 + max_lung

print(lung)
print(succ)

#solutia la pb = max din vectorul lung
i_max=0
for i in range(1,n):
    if lung[i]>lung[i_max]:
        i_max=i
print("lungimea maxima ",lung[i_max])

while i_max!=-1:
    print(v[i_max], end=" ")
    i_max=succ[i_max]

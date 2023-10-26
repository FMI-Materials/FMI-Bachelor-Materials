w=[1,3,4,5]
v=[1,4,5,7]
n=4
g=7
t=[[0]*(g+1) for i in range(n)]
for i in range(n):
    for j in range(1, g+1):
        if j<w[i]:
            t[i][j]=t[i-1][j]
        else:
            t[i][j]=max(v[i]+t[i-1][j-w[i]], t[i-1][j])

j=g
i=n-1
sol=[]
while i>0 and j>0:
    if j<w[i]:
        i-=1
    elif  v[i]+t[i-1][j-w[i]]>t[i-1][j]:
        sol.append((w[i],v[i]))
        i-=1
        j-=w[i]
    else:
        i-=1
gt=0
pt=0
print(sol)
for i in range(len(sol)):
    gt+=sol[i][0]
    pt+=sol[i][1]
print(gt,pt)
n=5
m=6
v=[1,5,2,5,3]
w=[1,7,2,5,6,3]
#initializam matricea T de dimensiune (m+1)*(n+1)
T=[[0]*(m+1) for i in range(n+1)]

#incepem consruirea lui T
for i in range(1,n+1):
    for j in range(1,m+1):
        if v[i-1]==w[j-1]:
            T[i][j]=T[i-1][j-1]+1
        else:
            T[i][j]=max(T[i-1][j],T[i][j-1])

#lungimea celui mai lung subsir se va afla in T[n][m]
print('Lungimea maxima a subsirului comun este: ',T[n][m])
print('Sirul este:',end=' ')
def parcurg(n,m):

   if n>0 and m>0:
        if T[n][m]==max(T[n-1][m],T[n][m-1]):
            if T[n][m]==T[n-1][m]:
                parcurg(n-1,m)
            else:
                parcurg(n,m-1)
        else:
            parcurg(n-1,m-1)
            print(v[n-1],end=' ')
parcurg(n,m)
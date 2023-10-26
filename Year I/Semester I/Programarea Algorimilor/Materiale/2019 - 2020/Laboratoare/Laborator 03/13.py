n=int(input())

matrix = []

x=1
for i in range(n):
    a = []
    for j in range(n):
        a.append(x)
        x+=1
    matrix.append(a)

if n%2==0:
    lim=n//2
else:
    lim=n//2+1
l=[]
for k in range(lim):
    for j in range(k,n-k):
        l.append((k,j))
    for i in range(k+1,n-k):
        l.append((i,n-k-1))
    for j in range(n-k-2,k,-1):
        l.append((n-k-1, j))
    for i in range(n-k-1,k,-1):
        l.append((i,k))
print(l)
spirala=[]
for t in l:
    spirala.append(matrix[t[0]][t[1]])
print(spirala)

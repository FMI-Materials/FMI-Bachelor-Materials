f=open("date.in")
x=f.readline()
v=x.split()
n=int(v[0])
m=int(v[1])
a=[]
for line in f:
    v=line.split()
    l=[]
    for j in range(m):
       l.append(int(v[j]))
    a.append(l)
print(a)
t=[[0 for i in range(m) ]for j in range (n)]
t[0][0]=a[0][0]
for i in range(n):
    for j in range ( m):
        if i>0 and j==0:
            t[i][j]=a[i][j]+t[i-1][j]
        elif i==0 and j>0:
            t[i][j] = a[i][j] + t[i][j-1]
        elif i>0 and j>0:
            t[i][j] = a[i][j] + max(t[i - 1][j], t[i][j-1])
print(t[n-1][m-1])
i=n-1
j=m-1
afis=[(i+1,j+1)]
while i>0 or j>0:
     if i>0 and j>0:
         if a[i][j-1]>a[i-1][j]:
             afis.append((i+1,j))
             j-=1
         else:
             afis.append((i,j+1))
             i-=1
     elif i==0:
        afis.append((i+1,j))
        j-=1
     elif j==0:
            afis.append((i,j+1))
            i-=1
afis.reverse()
print(afis)

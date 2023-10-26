f=open("intrare.txt","r")
n=int(f.readline())
a=[None]*(n+1)
for i in range(n):
    a[i+1]=[0]*(n+1)
for line in f:
    l=line.split()
    i=int(l[0])
    j=int(l[1])
    a[i][j]=a[j][i]=1

for i in range(n):
    print(a[i+1][1:])

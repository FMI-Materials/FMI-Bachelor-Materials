n=int(input())
z1=float(input())
max=0
for i in range(2, n+1):
    z2=float(input())
    if z2>z1 and z2-z1>max:
        max=z2-z1
        x=i
    z1=z2

print(max, x-1, x)

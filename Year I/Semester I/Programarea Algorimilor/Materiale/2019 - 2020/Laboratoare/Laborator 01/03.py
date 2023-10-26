x=int(input())
n=int(input())
p=int(input())
m=int(input())
d=0
for i in range(1,m+1):
   
    if i!=1 and (i-1) % n==0:
        x=x*(100-p)/100
    d+=x
print(d)
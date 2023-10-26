n=int(input())
l=[]
while n>0:
    l.append(n%10)
    n=n//10
l.sort()
s=""
for i in l:
    s+=str(i)
x=len(l)-1
a=""
while x>=0:
    a+=str(l[x])
    x-=1
poz=0
while s[poz]=="0":
    poz+=1
min=s[poz:]+s[:poz]
max=int(a)
min=int(min)
print(min, max)
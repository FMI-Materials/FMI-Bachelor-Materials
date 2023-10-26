l1=int(input())
l2=int(input())
s=l1*l2
l1, l2=min(l1,l2), max(l1,l2)
while l1< l2:
    l2-=l1
    l1, l2 = min(l1, l2), max(l1, l2)
l=l1
a=l*l
n=s//a
print(l,n)
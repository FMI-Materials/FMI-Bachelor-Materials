a=[(1,9),(3,14),(2,8),(2,15),(3,6),(4,9)]
l=sorted(a,key=lambda x: x[1])
i=0
max=0
for x in l:
    f=i+x[0]
    if f>x[1]:
        d=f-x[1]
        if d>max:
            max=d
    i=f
print(max)
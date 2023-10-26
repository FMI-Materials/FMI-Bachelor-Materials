a=[10, 12, 6, 3, 9, 15, 2, 8, 14, 10, 11, 6]
k=1
d={k: [a[0]]}
for i in range(1,len(a)):
    ok=False
    for x in d:
        if a[i]<d[x][-1]:
            d[x].append(a[i])
            ok=True
            break
    if ok==False:
        k+=1
        d[k]=[]
        d[k].append(a[i])
print(d)



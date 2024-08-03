s=input()
d={}
for x in s:
    if x in d:
        d[x]+=1
    else:
        d[x]=1
for x in d:
    print(x,d[x], sep=" ")
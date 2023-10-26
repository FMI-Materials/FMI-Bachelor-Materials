a=[(1,2), (1,4), (2,3), (4,5)]
a=sorted(a,key=lambda x: x[1])
cui=-1

sol=[]
for x in a:
    if x[0]<=cui<=x[1]:
        continue
    if x[0]>cui:
        sol.append(x[1])
        cui=x[1]
    if x[1]<cui:
        sol.pop()
        sol.append(x[1])
        cui=x[1]
print(len(sol))

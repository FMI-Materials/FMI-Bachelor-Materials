nume=input()
f=open(nume,"r")
g=open("rime.txt", "w")
d={}
for x in f:
   x=x.strip('\n')
   n=len(x)
   if x[n-2:] in d:
       d[x[n-2: ]].append(x)
   else:
       d[x[n - 2:]]=[]
       d[x[n - 2:]].append(x)
print(d)
for x in d:
    if len(d[x])>=2:
         d[x].sort()
         for y in d[x]:
            g.write(str(y)+" ")
         g.write("\n")

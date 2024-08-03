f=open("prob8.txt","r")
p=f.readline()

f.close()
cuv=input()
s=set()
for x in cuv:
    if x not in s:
        s.add(x)

l=p.split()
for x in l:
    x=x.strip(".,?!;:")
    ok1=True
    ok2=True
    for a in s:
        if a not in x:
            ok1=False
            break
    for a in x:
        if a not in s:
             ok2 = False
             break
    if ok1==True and ok2==True:
        print(x)


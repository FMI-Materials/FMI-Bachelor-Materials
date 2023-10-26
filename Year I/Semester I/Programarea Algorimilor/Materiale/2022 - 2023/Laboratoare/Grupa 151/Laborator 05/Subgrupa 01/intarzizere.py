f=open("activitati.txt")
n=f.readline()
l=[]
for line in f.readlines():
    a,b=line.split()
    l.append((int(a), int(b)))

l.sort(key=lambda ob: ob[1])

t=0
intarziere=0
for i in l:
    print(t, '-->', t + i[0], 'termen limita: ', i[1])
    t+=i[0]
    if t>i[1]:
        intarziere=max(intarziere, t-i[1])
print(intarziere)

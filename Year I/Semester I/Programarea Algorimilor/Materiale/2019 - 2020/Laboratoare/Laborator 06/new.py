f=open("graf.txt","r")
cuv=f.readline()
cuv=cuv.strip('\n')
n=int(f.readline())
m=int(f.readline())
d={}
for i in range(m):
    line = f.readline()
    line = line.strip("\n")
    x = line.split()
    a=int(x[0])
    b=int(x[1])
    if a in d:
        d[a].append(b)

    else:
        d[a]=[]
        d[a].append(b)
    if b in d:
            d[b].append(a)

    else:
            d[b] = []
            d[b].append(a)
plec=int(f.readline())
ajung=int(f.readline())
f.close()
d={
    1:[2, 6],
    2:[1, 3, 4, 6],
    3:[2,4,5,6],
    4:[2,3,8],
    5:[3],
    6:[1,2,3,7],
    7:[6],
    8:[4]
}
df=[]
vizitat=[]
plec=2
df.append(plec)
vizitat.append(plec)
while df !=[]:
    tata=df[-1]
    for fiul in d[tata]:
        if fiul not in vizitat:

             df.append(fiul)
             vizitat.append(fiul)
             break
    else:
             df.pop(-1)
for x in vizitat:
    print(x)
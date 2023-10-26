r=open("tis.txt")
f=r.readline().split()
for i in range(0,len(f)):
    f[i]=(int(f[i]), i)

f.sort()
t=0
till_now = 0
for i in range(len(f)):
    print(f[i][1])
    t+=till_now+f[i][0]
    till_now += f[i][0]
print(t / len(f))

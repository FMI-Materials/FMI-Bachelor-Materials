f=open("cheltuieli.txt","r")
x=f.read()
f.close()
l=x.split()
v=[]
for t in l:
    if t.find('.')!=-1:
        a=t.split(".")
        if len(a)==2 and a[0].isdecimal()==True and a[1].isdecimal()==True:
            m=a[0]+a[1]
            n=int(m)
            p=10**len(a[1])
            n=n/p
            print(n)
            v.append(n)
    elif t.isdecimal()==True:
        print(t)
        v.append(int(t,10))
s=0
for i in range(0,len(v)-1,2):
    s+=v[i]*v[i+1]
print(s)
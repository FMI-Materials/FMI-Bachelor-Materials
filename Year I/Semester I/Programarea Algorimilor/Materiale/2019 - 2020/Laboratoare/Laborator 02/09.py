p=input()
l=[]
for i in range(len(p)):
    if p[i]=='$':
        j=i+1
        nr=0
        while j<len(p) and p[j].isdecimal()==True:
            nr=nr*10+int(p[j])
            j+=1
        l.append(nr)
print(l[0],l[1])
if l[len(l)-1]==l[len(l)-2]:
    print("s-au inteles")
else:
    print("nu s-au inteles")
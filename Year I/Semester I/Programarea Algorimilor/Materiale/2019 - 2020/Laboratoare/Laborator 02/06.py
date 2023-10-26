p=input()
nr=0
s=0
for x in p:
    if x.isdigit()==True:
        nr=nr*10+int(x,10)
    else:
        s+=nr
        nr=0
print(s)
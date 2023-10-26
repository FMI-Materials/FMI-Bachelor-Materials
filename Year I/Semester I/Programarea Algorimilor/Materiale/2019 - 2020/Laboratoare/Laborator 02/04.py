a=input()
b=input()
ok=True
for i in a:
    if i in b:
        p=b.find(i)
        b=b[:p]+b[p+1:]
    else:
        ok=False
        break

if ok==True and len(b)==0 :
    print("sunt anagrame")
else:
    print("nu sunt anagrame")
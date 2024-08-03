f=open("prob11.txt","r")
s=f.read()
l=s.split("+")
d=[]
for x in l:
    x=x.strip('"\n')
    poz=x.find(":")
    cuv=x[:poz]
    nr=0
    lung=len(cuv)
    for i in range(poz,len(x)-lung):
        if x[i:i+lung]==cuv and x[i-1].isalpha()==False and x[i+lung].isalpha()==False:
            nr+=1
            


    for a in x:
        if "~"==a:
            nr+=1

    d.append((cuv,nr))

print(d)
s=input()
l=[int(x,10) for x in s if x.isdecimal()==True]
if len(l)==0:
    print("nu s-au dat numere")
elif len(l)==1:
    print("max1=max2=", l[0])
elif len(l)>=2:
    if l[0]<l[1]:
        max1=l[1]
        max2=l[0]
    else:
        max1=l[0]
        max2=l[1]
    for i in range(2,len(l)):
        if l[i]>max1:
            max2=max1
            max1=l[i]
        elif l[i]>max2:
            max2=l[i]
    print(max1,max2)
def munte(a,p,q):

    if q==p:
        return a[q]
    else:
        mid=(p+q)//2
        max1= munte(a,p,mid)
        max2=munte(a,mid+1,q)
        if max1>max2:
            return max1
        else:
            return max2
a=[4,8,10,11,5]
print(id(a))
print(id(a))
#print(munte(a,0,len(a)-1))



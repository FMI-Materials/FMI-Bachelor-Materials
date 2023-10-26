def inter(p, m, q):
    #interclasare siruri sortate a(p,m) si a(m+1,q)
    i=p
    global a
    j=m+1

    b=[]
    while i<=m and j<=q:
        if a[i]<a[j]:
            b.append(a[i])
            i+=1
        else:
            b.append(a[j])
            j+=1
    while i<=m:
        b.append(a[i])
        i += 1
    while j<=q:
        b.append(a[j])
        j += 1
    #transfer in a
    a[p:q+1]=b.copy()
def ms(p, q):
    if p<q:
        m=(p+q)//2
        ms(p, m)
        ms(m+1, q)
        inter(p, m, q)
a=[1,5,2,3,9,3]
ms(0,5)
print(a)
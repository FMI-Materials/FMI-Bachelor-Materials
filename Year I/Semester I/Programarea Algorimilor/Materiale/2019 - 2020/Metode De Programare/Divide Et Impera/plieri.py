def pliaza (p,q):
    if p==q:
        ef[p]=1
    else:
        if (q-p+1)%2!=0:
            ls=(p+q)/2-1
        else:
            ls=(p+q)/2
        ld=(p+q)/2+1
        pliaza(p,ls)
        for i in range(p,ls+1):

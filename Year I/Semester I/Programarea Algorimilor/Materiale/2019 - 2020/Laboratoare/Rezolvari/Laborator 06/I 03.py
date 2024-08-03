def prima(l,pm, PM, x, n):
    mid=(pm+PM)//2
    poz=-1
    if l[mid]==x:
         poz=mid
         while l[poz]==x:
             poz-=1
         poz+=1
    else:
        if v[mid]>val:
            prima(l,pm,mid,x,n)
        else:
            prima(l,mid+1,PM,x,n)
    return poz
def ultima(l,pm, PM, x, n):
    mid=(pm+PM)//2
    poz=-1
    if l[mid]==x:
         poz=mid
         while poz<n and l[poz]==x :
             poz+=1
         poz-=1
    else:
        if v[mid]>val:
            ultima(l,pm,mid,x,n)
        else:
            ultima(l,mid+1,PM,x,n)
    return poz



def contor (l,x,n):
    #+1 cazul cu -1
    return ultima(l,0,n,x,n)-prima(l,0,n,x,n)

l=[1,2,2,3,3,3]
print(prima(l,0,6,3,6))
print(ultima(l,0,6,3,6))
print(contor(l,3,6)+1)
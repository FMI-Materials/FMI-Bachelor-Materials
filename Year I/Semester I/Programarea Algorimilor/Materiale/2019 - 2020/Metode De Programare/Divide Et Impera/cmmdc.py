def cmmdc( x, y): #algoritm p-zis de cmmdc
    x,y=min(x,y), max(x,y)
    while x<y:
        y-=x
        x, y = min(x, y), max(x, y)
    return x
def divide( p,q): #alg divide
    global a
    if q-p<=1 : #doua pozitii consecuitve in vector
        return cmmdc(a[p], a[q])
    else:
        m=(p+q)//2 #lucrez cu mijlocul
        return cmmdc(divide(p,m),divide(m+1,q))
#impart vectorul in 2 jumatati si tot asa pana ajung la 2 nr consecutive
a=[6,21,18,21]
print(divide(0,3))

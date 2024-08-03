def var(*args):
    nr=0
    if len(args)>0:
        for x in args:
            l=[]
            while x>0:
                l.append(x%10)
                x=x//10
            m=max(l)
            if m!=0:
                nr=nr*10+m
    return nr
l=[4251, 73, 8, 133]
print (var(*l))
def func(a, b, c):
    x=var(a,b,c)

    while x>0:
        if x%10!=1:
            return False
        x=x//10
    return True
print(func(100,17,1))
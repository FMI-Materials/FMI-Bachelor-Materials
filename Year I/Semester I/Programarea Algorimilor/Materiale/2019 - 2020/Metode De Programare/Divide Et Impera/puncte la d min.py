def cp(x,y):
    global i
    if len(x)==2:
        return abs(x[1]-x[0])
    elif len(x)==3:
        x.sort()
        return x[1]-x[0]
    xs=x[i]
    xd=x[i+1]

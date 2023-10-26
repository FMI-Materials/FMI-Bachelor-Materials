def clos(x, y):
    if len(x)==2:
        return x[1]-x[0]
    if len(x)==3:
        d1=x[1]-x[0]
        d2=x[2]-x[1]
        if d1<d2:
            return d1
        else:
            return d2
    for x in y:
        if
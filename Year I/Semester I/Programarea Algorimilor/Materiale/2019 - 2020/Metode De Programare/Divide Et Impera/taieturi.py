def taie(xs, ys, l, h):
    global gauri,am,xm,ym
    gasit=False
    for x in gauri:
        if xs<x[0]<xs+l and ys<x[1]<ys+h:
            #am gasit o gaura in placa mea
            #despart in 4 subprobleme
            taie(xs, ys, x[0]-xs, x[1]-ys)
            taie(x[0], ys, xs+l-x[0], x[1]-ys   )
            taie(x[0], x[1], xs+l-x[0], ys+h-x[1] )
            taie(xs, x[1],x[0]-xs ,ys+h-x[1])
            gasit=True
    if gasit==False:
        a=l*h
        if a>am:
            am=a
            xm=xs
            ym=ys
gauri=[(2,4),(3,3),(4,4)]
am=0
xm=ym=0
taie(1, 2, 4, 3)

print(am,xm,ym, sep=" ")
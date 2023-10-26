def divide(x,y,m,n):
    global a
    if m==n:
        return a[m][n]
    else:
        return divide(0,0,m/2,n/2)
        return divide


a=[[1, 2, 3, 4, 5],[2 ,4 ,6 ,1, 7],[1, 3, 4, 5, 9] ]
m=3
n=5
print(divide(0,0))
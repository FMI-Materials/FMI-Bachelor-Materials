def back (k):
    global sp,n,x
    if sp==n:
        print(* x[1:k])
    else:
            sp=0
            for i in range(n+1):
                x[k]=i
                if sp+x[k]<=n and x[k]>x[k-1]:
                    sp+=x[k]
                    back(k+1)

n=4
sp=0
x=[0]*(100)
back(1)

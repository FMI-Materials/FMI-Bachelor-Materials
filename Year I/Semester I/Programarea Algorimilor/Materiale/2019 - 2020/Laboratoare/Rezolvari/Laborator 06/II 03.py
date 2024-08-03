def bkt(k):
    global sol,n,s
    if s==n:
        print(*sol[1:k])

    else:
            for i in range(sol[k-1]+1,n-k+3):
                sol[k]=i
                s+=i
                bkt(k+1)
                s-=i

n=int(input())
sol=[0]*(n+1)

s=0
bkt(1)

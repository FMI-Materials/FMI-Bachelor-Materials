
def bkt(k):
    global sol,n,s
    if s==n:
        print(*sol[1:k])
    else:
        sol[k]=0
        while sol[k]+s<n:
            sol[k]+=1
            s+=sol[k]
            bkt(k+1)
            s-=sol[k]

n=int(input())
sol=[-1]*(n+1)
s=0
bkt(1)
'''
#al treilea punct
def bkt(k):
    global sol,n,s
    if s==n:
        print(*sol[1:k])
    else:

            for i in range(sol[k-1]+1,n-k+3):#sol[k-1],n-k+3 pt pct 2
                sol[k]=i
                s+=i
                bkt(k+1)
                s-=i

n=int(input())
sol=[0]*(n+1)
#sol[0]=1 pt pct 2
s=0
bkt(1)
'''
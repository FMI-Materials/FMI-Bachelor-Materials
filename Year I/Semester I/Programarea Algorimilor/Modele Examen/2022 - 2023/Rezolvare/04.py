n = int(input("n: "))
sol = [0] * (n+1)

def bkt(k):
    global n,sol
    for i in range(1,n+1):
        sol[k] = i
        if sol[k] not in sol[:k]:
            if k == n:
                print(*sol[1:])
            else:
                bkt(k+1)

bkt(1)
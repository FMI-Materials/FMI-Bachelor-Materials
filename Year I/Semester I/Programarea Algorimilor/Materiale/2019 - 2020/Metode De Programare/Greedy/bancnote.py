b={1,10,500,5,100,50}
s=123
l=sorted(b, reverse=True)
sol=[]
n=0
for x in l:
    if x<s:
        nr=s//x
        s=s%x
        sol.append((x,nr))
        n+=nr
print(*sol)
print(n)



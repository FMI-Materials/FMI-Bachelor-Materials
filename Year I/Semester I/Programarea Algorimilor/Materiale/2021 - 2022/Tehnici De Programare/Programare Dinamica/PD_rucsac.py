def afis(i, gr):
    if i == 0 or gr == 0:
        return
    if (g[i] <= gr) and (s[i][gr] == c[i] + s[i - 1][gr - g[i]]):
        afis(i-1, gr-g[i])
        print(i,end=" ")
    else:
        afis(i - 1, gr)

f=open("rucsac.in")
g=[0]
g.extend([int(x) for x in f.readline().split()])
c=[0]
c.extend([int(x) for x in f.readline().split()])
G=int(f.readline())

n=len(g)-1

s=[[0 for i in range(G+1)] for j in range(n+1)]


for gr in range(G+1):
    s[0][gr]= 0
for i in range(n+1):
    s[i][0]=0

for i in range(1,n+1):
    for gr in range(1,G+1):
        if g[i] <= gr:
            if c[i]+s[i-1][gr-g[i]] > s[i-1][gr]:
                s[i][gr]=c[i]+s[i-1][gr-g[i]]
            else:
                s[i][gr]=s[i-1][gr]
        else:
            s[i][gr]=s[i-1][gr]
print("matricea castigurilor pentru subprobleme:")
for linie in s:
    print(*linie)

print(f"Castigul total {s[n][G]}")


print("obiectele incarcate determinate folosind relatia de recurenta - varianta iterativa")
gr=G
i=n
while gr > 0 and i > 0:
    if (g[i] <= gr) and (s[i][gr] == c[i] + s[i - 1][gr - g[i]]):
        print(i, end=" ")
        gr = gr - g[i]
    i-=1

print()
print("obiectele incarcate determinate folosind relatia de recurenta - varianta recursiva")
afis(n, G)

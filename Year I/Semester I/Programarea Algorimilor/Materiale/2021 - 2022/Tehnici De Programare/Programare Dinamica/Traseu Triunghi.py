f=open("traseu.in")
t = [[int(x) for x in linie.split()] for linie in f]
f.close()
n = len(t)
s = [[0 for j in range(i+1)] for i in range(n)]
#s[i][j]=suma max care se poate obtine pornind din (i,j)

#stim sa calculam direct ultima linie din s = ultima linie din t
#s[n-1][:]=t[n-1] #ls[1:2]=[3,4]
for i in range(n):
    s[n-1][i]=t[n-1][i]

#calculam s de jos in sus
for i in range(n-2,-1,-1):
    for j in range(i+1):
        s[i][j]=t[i][j]+max(s[i+1][j],s[i+1][j+1])

print("solutii subprobleme: ")
for linie in s:
    print(*linie)

print("suma maxima este ", s[0][0])

j = 0 #coloana
for i in range(n-1): #linie
    print(f"({i+1},{j+1}) ", end="")
    if s[i+1][j+1]>s[i+1][j]:
        j += 1
print(f"({n},{j+1}) ", end="")
fin = open("obiecte.txt")
n = int(fin.readline())
L=[]
for i in range(n):
    s = fin.readline()
    s = s.split()
    L.append([int(s[0]),int(s[1])])
G = int(fin.readline())
L.sort(key = lambda x : x[0]/x[1])

g = 0
val = 0
i = n-1
while g < G and i >= 0:
    val += L[i][0]/L[i][1] * min(L[i][1], G-g)
    g += L[i][1]
    i -= 1

print(val)

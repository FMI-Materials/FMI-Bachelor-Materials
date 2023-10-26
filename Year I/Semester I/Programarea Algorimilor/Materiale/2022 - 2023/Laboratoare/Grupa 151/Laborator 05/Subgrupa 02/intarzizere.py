fin = open("activitati.txt")
n = int(fin.readline())

L = []
for i in range(n):
    line = fin.readline()
    p, u = line.split()
    L.append((int(p), int(u)))

L.sort(key = lambda x: x[1])

t = 0
maxim = 0
for i in range(n):
    t += L[i][0]
    if t > L[i][1]:
        maxim = max(maxim, t-L[i][1])

print (maxim)


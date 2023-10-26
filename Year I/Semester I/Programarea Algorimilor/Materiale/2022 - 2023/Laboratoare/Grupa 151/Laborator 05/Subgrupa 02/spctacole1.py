fin = open("spectacole.txt")

linii = [line.strip() for line in fin.readlines()]
n = len(linii)

L = []
for i in range(n):
    timpi, nume = linii[i].split(" ", 1)
    timp1, timp2 = timpi.split("-")
    L.append((timp2, timp1, nume))

L.sort()
u = L[0][0]
sol = []
sol.append(L[0])
for i in range(1, n):
    if L[i][1] > u:
        sol.append(L[i])
        u = L[i][0]

for i in range(len(sol)):
    print("{}-{} {}".format(sol[i][1],sol[i][0],sol[i][2]))

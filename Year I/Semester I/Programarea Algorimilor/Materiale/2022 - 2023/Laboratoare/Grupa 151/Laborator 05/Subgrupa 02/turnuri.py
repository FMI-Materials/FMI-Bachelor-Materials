fin = open("cuburi.txt")

n = int(fin.readline())
L = []
for i in range(n):
    s = fin.readline()
    s = s.split()
    L.append([int(s[0]),s[1]])

L.sort()
turn = 0
last_color=""
last_width=L[n-1][0]+1
for i in range(n-1,-1,-1):
    if L[i][0] < last_width and L[i][1] != last_color:
        last_width = L[i][0]
        last_color = L[i][1]
        print("{} {}".format(L[i][0],L[i][1]))
        turn += L[i][0]

print()
print("Lungimea turnului: {}".format(turn))
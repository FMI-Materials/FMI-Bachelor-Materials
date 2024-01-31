n = int(input())
x = []
y = []

for i in range(n):
    coord = [int(x) for x in input().split()]
    x.append(coord[0])
    y.append(coord[1])

# aflam daca este x-monoton

xmin = x[0]
indexMin = 0
xmax = x[0]
indexMax = 0

for i in range(len(x)):
    if x[i] < xmin:
        xmin = x[i]
        indexMin = i
    if x[i] > xmax:
        xmax = x[i]
        indexMax = i

if indexMin < indexMax:
    index = indexMin
    i = indexMin
    j = indexMax
else:
    index = indexMax
    i = indexMax
    j = indexMin

check1 = True
check2 = True
n = len(x)

for value in range(n):
    
    if x[index] > x[(index + 1) % n] and i <= index < j:
        check1 = False
    if x[index] < x[(index + 1) % n] and (index < i or j <= index):
        check2 = False

    index = (index + 1) % n

if check1 == True and check2 == True:
    print("YES")
else:
    print("NO")

# aflam daca este y-monoton

ymin = y[0]
indexMin = 0
ymax = y[0]
indexMax = 0

for i in range(len(y)):
    if y[i] < ymin:
        ymin = y[i]
        indexMin = i
    if y[i] > ymax:
        ymax = y[i]
        indexMax = i

if indexMin < indexMax:
    index = indexMin
    i = indexMin
    j = indexMax
else:
    index = indexMax
    i = indexMax
    j = indexMin

check1 = True
check2 = True
n = len(y)

for value in range(n):
    
    if y[index] > y[(index + 1) % n] and i <= index < j:
        check1 = False
    if y[index] < y[(index + 1) % n] and (index < i or j <= index):
        check2 = False

    index = (index + 1) % n

if check1 == True and check2 == True:
    print("YES")
else:
    print("NO")
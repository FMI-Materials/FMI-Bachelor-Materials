s = input()
nr = "".join([x if x.isdigit() else ' ' for x in s])
nr = nr.split()
sumTotal = 0
for i in range(len(nr)):
    sumTotal += int(nr[i])
print(sumTotal)
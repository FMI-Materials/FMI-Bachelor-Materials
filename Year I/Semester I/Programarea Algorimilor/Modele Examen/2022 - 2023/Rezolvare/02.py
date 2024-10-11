n = int(input("n: "))
spectacole = []

for i in range(n):
    temp = input().split()
    temp[0] = int(temp[0])
    temp[1] = int(temp[1])
    temp.append(i+1)
    spectacole.append(temp)


sala = []
spectacole.sort(key=lambda x:x[1])
sala.append(spectacole[0])
for i in range(1,len(spectacole)):
    if spectacole[i][0] >= sala[-1][1]:
        sala.append(spectacole[i])

for spec in sala:
    print(f"S{spec[2]}: {spec[0]}-{spec[1]}")
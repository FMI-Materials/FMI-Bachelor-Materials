infile = open("spectacole.txt")
spectacole = []
for line in infile:
    program, nume = line.split(" ", 1)
    startHour, endHour = program.split("-", 1)
    spectacole.append((startHour, endHour, nume))
spectacole.sort(key= lambda ob: ob[1])
ans = [spectacole[0]]
for spectacol in spectacole:
    if spectacol[0] >= ans[-1][1]:
        ans.append(spectacol)
for spectacol in ans:
    print(str(spectacol))


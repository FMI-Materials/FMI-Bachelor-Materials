s = input()
name = "".join([x if x.isalpha() or x == '-' else ' ' for x in s])
name = name.split()
if len(name) > 2:
    print("Nume invalid")
else:
    for i in range(len(name)):
        name[i] = ' ' + name[i] + ' '
        for j in range(1, len(name[i])):
            if name[i][j - 1] == ' ' or name[i][j - 1] == '-':
                if not(name[i][j].isupper()):
                    print("Nume invalid")
                    break
        else:
            currName = name[i].split(" -")
            for j in range(len(currName)):
                if len(currName[j]) < 3:
                    print("Nume invalid")
                    break
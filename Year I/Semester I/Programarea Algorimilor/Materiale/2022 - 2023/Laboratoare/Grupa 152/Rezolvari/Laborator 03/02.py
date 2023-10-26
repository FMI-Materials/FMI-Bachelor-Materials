cin = open("Txt Files/cheltuieli.in")

s = cin.readline()


def digit(x):
    if x.isalpha():
        return ' '
    else:
        return x


nr = ''.join([digit(x) for x in s]).split()
s = 0
for i in range(0, len(nr), 2):
    s += float(nr[i]) * float(nr[i + 1])
print(s)
cin.close()

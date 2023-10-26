s, t = map(str, input().split())
poz = s.find(t)
while poz != -1:
    print(poz, end = " ")
    poz = s.find(t, poz + 1)
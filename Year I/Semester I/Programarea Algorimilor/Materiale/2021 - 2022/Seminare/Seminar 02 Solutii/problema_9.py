w = input()
p = int(input())
n = int(input())
rez = ""
for i in range(n):
    s = input()
    if (len(s) >= p + 2) and (w[-p:] == s[-p:]):
        rez = rez + s + " "
print(rez)
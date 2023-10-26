# a
def digit(x):
    if x.isalpha():
        return ' '
    else:
        return x

def letter(x):
    if x.isdigit():
        return ' '
    else:
        return x

s = input()
nr = ''.join([digit(x) for x in s])
nr = nr.split()
print(nr[1])
t = ''.join([letter(x) for x in s])
t = t.split()
for i in range(len(nr)):
    print(t[i] * int(nr[i]), end = "")

# b
s = input()
t = ""
while s:
    j = len(s) - len(s.lstrip(s[0]))
    t += str(j) + s[0]
    s = s.lstrip(s[0])
print(t)
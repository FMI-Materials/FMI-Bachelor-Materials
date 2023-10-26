def ex1(s):
    l = s.split('.')
    print(l)
    if len(l) == 1:
        return l[0]
    cifre = "0123456789"
    l[0] = l[0].rstrip(cifre)
    l[-1] = l[-1].lstrip(cifre)
    for i in range(1, len(l) - 1):
        l[i] = l[i].strip(cifre)
    return "".join(l)


s = input()
print(ex1(s))

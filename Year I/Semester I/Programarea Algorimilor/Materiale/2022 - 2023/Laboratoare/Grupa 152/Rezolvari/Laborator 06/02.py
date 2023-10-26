def ex2(s):
    cifre = "0123456789"
    for i in cifre:
        s = s.replace(i, '')
    return s


s = input()
print(ex2(s))

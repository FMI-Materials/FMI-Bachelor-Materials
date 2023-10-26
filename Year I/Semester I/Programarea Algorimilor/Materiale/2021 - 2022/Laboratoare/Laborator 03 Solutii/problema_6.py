#pb 6
s = input()
#test palindrom s[i:j], i,.., j-1, s[i:j:pas]
if s == s[::-1]:
    print("palindrom")
else:
    print("nu este palindrom")

#semipalindrom: lungime para +  prima jumatate  = a doua jumatate
s = input()
if (len(s)%2==0) and (s[:len(s)//2]==s[len(s)//2:]):
    print("semipalindrom")
else:
    print("nu este semipalindrom")

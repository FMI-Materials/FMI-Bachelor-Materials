p=input()
for i in range(len(p)-1):
    if p[i]=='.' and p[i+1].isupper()==True:
        p=p[:i+1]+"\n"+p[i+1:]
l=p.split("\n")
print(*l, sep="\n")

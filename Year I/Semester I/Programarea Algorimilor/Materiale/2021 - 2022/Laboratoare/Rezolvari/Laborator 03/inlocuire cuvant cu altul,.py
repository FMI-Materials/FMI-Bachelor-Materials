p="acum acuma chiar acum incepe ora acum"  #acum -> mai incolo

s="acum"
t="mai incolo"
poz = p.find(s)

while poz != -1:
    if (poz+len(s) == len(p) or p[poz+len(s)] in " .,!") and (poz == 0 or p[poz-1] in " .,!"):
        p=p[:poz]+t+p[poz+len(s):]
    poz = poz+len(t)
    poz = p.find(s,poz)
print(p)
    
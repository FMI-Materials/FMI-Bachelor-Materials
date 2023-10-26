from string import digits, ascii_lowercase, ascii_uppercase
from random import choices
f=open("date.in","r")
g=open("date.out","w")
for x in f:
    l=x.split()
    s=""
    s=l[1].lower()+"."+l[0].lower()+"@myfmi.unibuc.ro"
    A = choices(ascii_uppercase)
    a = choices(ascii_lowercase, k=3)
    cif = choices(digits, k=4)
    parola = "".join(A + a + cif)
    s+=" "+parola
    g.write(s+'\n')


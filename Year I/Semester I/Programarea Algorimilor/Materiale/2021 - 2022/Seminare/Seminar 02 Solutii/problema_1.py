a=int(input("a="))
b=int(input("b="))
c=1
d=1
while d<a:
    c,d=d,c+d
if d<=b:
    print(d)
else:
    print("nu exista")
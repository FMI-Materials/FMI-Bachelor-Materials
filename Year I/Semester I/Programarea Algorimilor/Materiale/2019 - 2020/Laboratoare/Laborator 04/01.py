from math import sqrt
def ipotenuza(a, b):
    ip=a*a+b*b
    return sqrt (ip)

b=int(input())
g=open("triplete_pitagoreice.txt","w")
for a in range(1,b):
    ip= ipotenuza(a,b)
    if int(ip)==ip:
        ip=int(ip)
        g.write("("+str(a)+","+str(b)+","+str(ip)+") ")
g.close()
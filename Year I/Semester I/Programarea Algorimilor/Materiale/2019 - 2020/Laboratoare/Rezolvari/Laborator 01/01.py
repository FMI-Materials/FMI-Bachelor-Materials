a=int(input())
b=int(input())
c=int(input())
d=b*b-4*a*c
rad=d**0.5
if d<0 :
    print("nu are radacini reale")
elif d==0:
    print("x1=x2=", -b/(2*a) )
else:
    x1=(-b+rad)/(2*a)
    x2=(-b-rad)/(2*a)
    print(" solutiile sunt x1={} si x2={}".format (x1, x2))
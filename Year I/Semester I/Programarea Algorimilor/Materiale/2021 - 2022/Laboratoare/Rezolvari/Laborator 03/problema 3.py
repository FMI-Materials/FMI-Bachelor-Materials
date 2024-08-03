n= int (input("n="))

a = b = 1

while b <= n:
    a, b = b, a+b

while n:
    if a <= n:
        n-= a
        print (a, end=' ')
    a,b = b-a , a



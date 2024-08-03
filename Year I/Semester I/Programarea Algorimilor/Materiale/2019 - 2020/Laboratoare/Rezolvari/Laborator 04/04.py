def prim (a):
    for d in range(2,a//2+1):
        if a%d==0:
            return 0
    return 1
def generator ():
    x=2
    while True:
        if prim(x)==1:
            yield x
        x+=1
n=9
'''
for x in generator():

   if x>n:
       break
   else:
       print(x)
'''
nr=1
for x in generator():

   if nr>n:
       break
   else:
       print(x)
       nr+=1


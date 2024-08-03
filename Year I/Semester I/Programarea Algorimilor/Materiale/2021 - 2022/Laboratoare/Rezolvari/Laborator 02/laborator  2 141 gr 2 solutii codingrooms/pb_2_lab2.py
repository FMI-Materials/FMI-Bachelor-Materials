#problema 2 cu find
t=input("t=")
s=input("s=")
p=s.find(t)
while p!=-1:
      print(p, end=" ")
      p=s.find(t,p+1)
print()

try:
    p=s.index(t)
    while True: #p!=-1:
        print(p, end=" ")
        p=s.index(t,p+1)
except:
    pass
print()
print("am terminat cu bine") 


fin=open("tis.txt")
l=[]
i=0
p=fin.readline()
p=p.split()
for timp in p:
    l.append((int(timp),i))
    i+=1
l.sort()
timp_mediu = 0
till_now = 0
for persoana in l:
    print(persoana[1],end=" ")
    timp_mediu += persoana[0] + till_now
    till_now += persoana[0]
fin.close()
print(timp_mediu / len(l))

# L = sorted([(int(num), i) for i, num in enumerate(fin.readline().rstrip().split())])
# print(L)
lista=[('a',2, 100),('b',1,19), ('c',2,27), ('d',1,25),('e',3,15)]
from collections import deque
lis=deque(sorted(lista, key=lambda x:x[1],reverse=True))
print(lis)
k=lis[0][1]
q=deque([])
s=[0]*(k+1)
k1=k
while lis!=deque([])and k>=1 :

    while  lis!=deque([]) and lis[0][1]>=k:

        #inserare!!!!!!!!!!!!!!!
        if q==deque([]):
            q.append(lis[0])

        elif lis[0][2]>=q[0][2]:
            #print("dcaici", lis[0][2],q[0][2])
            q.appendleft(lis[0])

        elif lis[0][2]<=q[len(q)-1][2]:
            q.append(lis[0])

        else:
           i=1
           while q[i-1][2]>=lis[0][2] and lis[0][2]<=q[i][2] :
                i+=1

           q.insert(i,lis[0])

        lis.popleft()


    s[k]=q.popleft()

    k-=1
print(str(k1)+"\n"+"proiecte:")

for i in range(1,len(s)):
    if i==1:
        print(s[i][0])
    else:
        print(s[i][0], sep=",")
print("\n"+"profit:")
T=0
for i in range(1,len(s)):
    if i==1:
        print(s[i][2])
    else:
        print(s[i][2], sep="+")
    T+=int(s[i][2])
print("=",T)
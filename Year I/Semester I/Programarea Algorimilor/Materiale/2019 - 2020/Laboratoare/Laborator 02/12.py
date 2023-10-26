s1=input()
s2=input()
S1=s1
S2=s2
#s1 <op> s2
print(s1,s2)
while s1[len(s1)-1]==s2[0]:
    x=s2[0]
    while x in s1:
        s1=s1.strip(x)
    while x in s2:
        s2=s2.strip(x)
    print(s1, s2)
a=len(s1+s2)
print(s1+s2)
#s2 <op> s1
print(S2,S1)
while S2[len(S2)-1]==S1[0]:
    x=S1[0]
    while x in S1:
        S1=S1.strip(x)
    while x in S2:
        S2=S2.strip(x)
    print(S2, S1)
b=len(S2+S1)
print(S2+S1)
if a<b:
    print(2)
else:
    print(1)
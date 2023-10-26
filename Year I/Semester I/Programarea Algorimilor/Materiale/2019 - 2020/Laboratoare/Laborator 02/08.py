p=input()
#punctul a
vocale="AEIOUaeiou"
nou=""
for x in p:
    if x in vocale:
        nou+=x+"p"+x.lower()
    else:
        nou+=x
print(nou)
#punctul b
s=input()
nou=""
for i in range(len(s)-1):
    if s[i+1].isalpha()==False and s[i].isalpha()==True:
        nou+=s[i]+'p'+s[i].lower()
    else:
        nou+=s[i]
nou+=s[len(s)-1]

print(nou)
n=""
for x in nou:
    if x!='-':
        n+=x
print(n)
a=""
i=0
while i< len(nou)-3:
    if nou[i].lower()==nou[i+2].lower() and nou[i+1]=='p' and nou[i+3].isalpha()==False:
        a+=nou[i]+nou[i+3]
        i+=4
    else:
        a+=nou[i]
        i+=1
print(a)
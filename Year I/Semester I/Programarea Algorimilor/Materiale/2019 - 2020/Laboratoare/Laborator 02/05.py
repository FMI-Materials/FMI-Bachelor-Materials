s=input()
k=int(input())
k=k%26
nou=""
#criptare
for x in s:
    if x.isalpha()==True:
       n=ord(x)+k
       if n>ord('z'):
           n=ord('a')-1+n-ord('z')
       nou+=chr(n)
    else:
        nou+=x

#decriptare
s=nou

nou=""
for x in s:
    if x.isalpha()==True:
       n=ord(x)-k
       if n<ord('a'):
           n=ord('z')-(ord('a')-n)+1
       nou+=chr(n)
    else:
        nou+=x
print(nou)
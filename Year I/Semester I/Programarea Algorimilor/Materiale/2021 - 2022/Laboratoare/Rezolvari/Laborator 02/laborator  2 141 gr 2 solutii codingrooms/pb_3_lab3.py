s=input("s=")
i=0
j=len(s)
while i<j:
    #t=s[i:j]
    #t=t.center(10)
    print(s[i:j].center(10))
    i+=1
    j-=1


i=0
j=len(s)
while i<j:
    #t=s[i:j]
    #t=t.center(10)
    print(f"{s[i:j]:^10}") #aliniere pe 10 caractere ^ = centrat
    i+=1
    j-=1

p=input()
s=input()
t=input()
S=len(s)
n=len(p)
#adaug spatiu si la inceput si la sfarsit
p=" "+p+" "
for i in range(1,n):
    cop=p[i:i+S]
    if cop==s  and p[i-1].isalpha()==False and p[i+S].isalpha()==False:
        p=p[:i]+t+p[i+S:]

p=p.strip(" ")
print(p)

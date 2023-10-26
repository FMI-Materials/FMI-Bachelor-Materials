f=open("cuvinte.txt","r")
l=[]
for line in f:
    line=line.strip("\n")
    l.append(line)
f.close()
g=open("cuv_sort.txt","w")
#l.sort(reverse=True)

#l=sorted(l,key=lambda x: (len(x),x))
l=sorted(l,key=lambda x: (len(x)))
print(l)
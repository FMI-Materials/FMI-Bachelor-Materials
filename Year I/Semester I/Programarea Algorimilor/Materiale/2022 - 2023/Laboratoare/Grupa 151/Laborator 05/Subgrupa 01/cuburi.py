file=open("cuburi.txt")
n=file.readline()
l=[]
for line in file.readlines():
    line=line.strip()
    l.append(line.split())
l.sort(key=lambda ob: int(ob[0]), reverse=True)
l_blocuri=[l[0]]

for i in l[1:]:
    if i[1] != l_blocuri[-1][1]:
        l_blocuri.append(i)

print(l_blocuri)




    
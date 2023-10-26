l=[(3,'a'),(4,'r'),(3,'r'),(2,'a')]
l=sorted(l,reverse=True, key=lambda x:x[0])
sol=[l[0]]
for i in range(1,len(l)):
    if l[i][1]!=sol[-1][1]:
        sol.append(l[i])
print(sol)
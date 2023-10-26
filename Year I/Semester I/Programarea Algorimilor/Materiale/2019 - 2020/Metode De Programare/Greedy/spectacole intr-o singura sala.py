a=[("10:00", "11:20", "scufita rosie"),("09:30", "12:10", "punguta cu doi bani"), ("08:20", "09:50", "vrajitorul din oz"),("11:30", "14:00", "capra cu trei iezi"), ("12:10", "13:10", "micul print"),("14:00", "16:00", "pov porc"), ("15:00", "15:30", "frumoasa adormita")]
l=sorted(a,key =lambda x: x[1])
sol=[l[0]]
for i in range(1,len(l)):
    if l[i][0]>sol[-1][1]:
        sol.append(l[i])
print(*sol)
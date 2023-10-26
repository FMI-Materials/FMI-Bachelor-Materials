n=int(input("numar activitati: "))
ls=[int(x) for x in input("durate: ").split()]
t=[(ls[i],i+1) for i in range(len(ls))]
print(t)
"""
i=0
t=[(int(x), i:=i+1) for x in input("durate: ").split()]
"""

t.sort()
print(t)
t_total=0
sum_t_anterior = 0
print("ordine de executare a activitatilor ")
for ti,i in t:
    sum_t_anterior+=ti
    t_total+=sum_t_anterior
    print(f"Activitatea {i} - a asteptat in total {sum_t_anterior}")
print(f"Timpul mediu de asteptare: {t_total/n:.2f}")
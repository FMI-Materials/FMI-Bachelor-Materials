from copy import deepcopy

def pct_a(nume):
    f=open(nume)
    L=[]
    for line in f.readlines():
        line=line.split()
        for i in range(len(line)):
            line[i]=int(line[i])
        L.append(line)
    f.close()
    return L

lista = pct_a("input.txt")
    
def pct_b(l):
    l = deepcopy(l)
    new_l = []
    mini=len(l[0])
    for i in l:
        a=min(i)
        while a in i:
            i.remove(a)
        if len(i)< mini:
            mini=len(i)
    for el in l:
        new_l.append(el[:mini])
    return new_l     

new_list = pct_b(lista)
print(new_list)

# c
for lista in new_list:
    for el in lista:
        print(el, end=" ")
    print()

for lista in new_list:
    print(*lista)


# d
def pct_d(k, lista):
    sol = set()
    for linie in lista:
        for el in linie:
            el = str(el)
            nrcif = len(el)
            if nrcif == k:
                sol.add(el)
    f = open("cifre.out", "w")
    sol = list(sol)
    sol.sort(reverse=True)
    print(*sol, file=f)
    # for el in sol:
    #     print(el, end=" ", file=f)
    # print

lista = pct_a("input.txt")
k = int(input())
pct_d(k, lista)

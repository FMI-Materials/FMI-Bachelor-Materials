def citire_intervale(nume_fisier):
    ls = []
    i=0
    with open(nume_fisier) as f:
        for linie in f:
            i=i+1
            s, t = (int(x) for x in linie.strip("[]\n").split(","))
            ls.append((i,[s,t])) #primul element- indicele activitatii, al doilea -intervalul de desfasurare (putea fi memorat si ca tuplu)
    return ls

def selectie_activitati(ls):
    def cheie_activitate(a):
        return a[1][1]  #a[0]=indicele activitatii, a[1]=intervalul de desfasurare, a[1][1]=timpul de terminare
    ls.sort(key=cheie_activitate)
    print(f"Activitati ordonate dupa terminare {ls}")
    rez=[]
    t_ultima_selectata=0
    rez.append(ls[0])

    for i in range(1,len(ls)):
        act_curenta=ls[i]
        if act_curenta[1][0]>t_ultima_selectata:
            t_ultima_selectata=act_curenta[1][1]
            rez.append(act_curenta)
    return rez

def afiseaza (ls):
    for(i,interval) in ls:
        print(f"activitatea {i}: [{interval[0]},{interval[1]}]")


ls = citire_intervale("intervale.in")
print(f"Activitati initiale {ls}")
afiseaza(selectie_activitati(ls))
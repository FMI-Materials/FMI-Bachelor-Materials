""" 6. Numãrul minim de sãli necesare pentru a programa mai multe spectacole
Fisierul “spectacole.txt” contine, pe câte un rând, ora de început, ora de 
sfârsit si numele câte unui spectacol. 
Sã se creeze o listã care sã continã, în tupluri formate din câte 3 siruri de 
caractere, cele 3 informatii despre fiecare spectacol. 

Sã se determine numãrul minim de sãli necesare k pentru a putea programa toate 
spectacolele, fãrã sã existe suprapuneri între spectacolele din aceeasi salã. 

În fisierul “sali.txt” sã se afiseze k si apoi spectacolele care au fost 
programate în fiecare dintre cele k sãli.

Indicatie de rezolvare:
-	Se sorteazã lista de spectacole crescãtor dupã ora de început.
-	Parcurgând lista sortatã, se alege câte un spectacol si se programeazã în 
oricare dintre sãlile disponibile (dacã spectacolul curent începe dupã ora de 
sfârsit a ultimului spectacol din acea salã) sau se programeazã într-o nouã 
salã (dacã în toate sãlile disponibile existã deja spectacole care se suprapun 
cu spectacolul curent). 

Exemplu:
evenimente.txt
15:00-16:30 j
11:00-12:30 d
09:00-10:30 a
13:00-14:30 f
14:00-16:30 h
11:00-14:00 e
15:00-16:30 i
09:00-12:30 b
13:00-14:30 g
09:00-10:30 c	

sali.txt
3 sali
(09:00-10:30 a), (11:00-12:30 d), (13:00-14:30 f), (15:00-16:30 j)
(09:00-12:30 b), (13:00-14:30 g), (15:00-16:30 i)
(09:00-10:30 c), (11:00-14:00 e), (14:00-16:30 h)
"""

f = open("06_evenimente.txt", "r")
spectacole = []
for x in f:
    x = x.strip("\n").replace("-"," ",1).split(" ",2)
    spectacole.append(tuple(x))
f.close()

spectacole.sort(key = lambda x : x[0])
# print(*sp, sep="\n")

k = 1
sali = [ [spectacole[0]] ]
for x in spectacole[1:]:
    for i in range(len(sali)):
        if x[0] >= sali[i][-1][1]:
            sali[i].append(x)
            break
    else:
        k += 1
        sali.append([x])

g = open("06_sali.txt", "w")
g.write(f"{k} sali\n\n")
for s in sali:
    g.write(", ".join([str(x) for x in s]) + "\n\n")
g.close()
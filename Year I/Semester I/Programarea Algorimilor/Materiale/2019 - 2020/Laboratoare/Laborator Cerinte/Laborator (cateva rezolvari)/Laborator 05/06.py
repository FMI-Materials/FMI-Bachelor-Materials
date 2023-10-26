""" 6. Num�rul minim de s�li necesare pentru a programa mai multe spectacole
Fisierul �spectacole.txt� contine, pe c�te un r�nd, ora de �nceput, ora de 
sf�rsit si numele c�te unui spectacol. 
S� se creeze o list� care s� contin�, �n tupluri formate din c�te 3 siruri de 
caractere, cele 3 informatii despre fiecare spectacol. 

S� se determine num�rul minim de s�li necesare k pentru a putea programa toate 
spectacolele, f�r� s� existe suprapuneri �ntre spectacolele din aceeasi sal�. 

�n fisierul �sali.txt� s� se afiseze k si apoi spectacolele care au fost 
programate �n fiecare dintre cele k s�li.

Indicatie de rezolvare:
-	Se sorteaz� lista de spectacole cresc�tor dup� ora de �nceput.
-	Parcurg�nd lista sortat�, se alege c�te un spectacol si se programeaz� �n 
oricare dintre s�lile disponibile (dac� spectacolul curent �ncepe dup� ora de 
sf�rsit a ultimului spectacol din acea sal�) sau se programeaz� �ntr-o nou� 
sal� (dac� �n toate s�lile disponibile exist� deja spectacole care se suprapun 
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
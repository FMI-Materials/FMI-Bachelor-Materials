""" 8. Planificarea proiectelor cu profit maxim
Se considerã o multime de proiecte, fiecare având un termen limitã si un 
profit asociat dacã proiectul este terminat pânã la termenul limitã. 
Fiecare proiect este realizat într-o singurã unitate de timp. 
Sã se planifice proiectele (fãrã a se suprapune ca timp) astfel încât sã se 
maximizeze profitul total. 

Fisierul “proiecte.txt” contine, pe fiecare linie, numele, termenul limitã 
si profitul asociat unui proiect. 

În fisierul “profit.txt” sã se afiseze succesiunea de proiecte alese si 
profitul total obtinut prin realizarea lor.

Indicatie de rezolvare:
-	Se sorteazã lista de proiecte descrescãtor dupã profit.
-	Folosind un dictionar care contine un numãr de intrãri egal cu maximul 
termenelor limitã, se va încerca planificarea fiecãrui proiect cât mai 
aproape de termenul sãu limitã.

Exemplu:
proiecte.txt
a 2 100
b 1 19
c 2 27
d 1 25
e 3 15	

profit.txt
T=3
proiecte: c, a, e
profit: 27+100+15 = 142
"""

f = open("8_proiecte.txt", "r")
proiecte = [(nume, int(termen), int(profit)) \
            for s in f for [nume, termen, profit] in [s.split()]]
f.close()

proiecte.sort(key = lambda x : x[2], reverse=True)
#print(proiecte)

max_termene = max([x[1] for x in proiecte])
L = [None for i in range(max_termene)]

for x in proiecte: # Solutia in O(n*n)
    for poz in range(x[1]-1, -1, -1):
        if L[poz] == None:
            L[poz] = x
            break

g = open("8_profit.txt", "w")
g.write(f"T = {max_termene}\n")
g.write("proiecte: " + ", ".join([x[0] for x in L]) + "\n")
g.write("profit: " + " + ".join([str(x[2]) for x in L]) \
        + " = " + str(sum([x[2] for x in L])) )
g.close()

# !!! Pentru alte rezolvari la problema 8,
#     a se vedea seminarele 5 si 6, gr 131.
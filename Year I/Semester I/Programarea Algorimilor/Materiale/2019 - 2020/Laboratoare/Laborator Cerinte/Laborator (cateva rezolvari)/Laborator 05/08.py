""" 8. Planificarea proiectelor cu profit maxim
Se consider� o multime de proiecte, fiecare av�nd un termen limit� si un 
profit asociat dac� proiectul este terminat p�n� la termenul limit�. 
Fiecare proiect este realizat �ntr-o singur� unitate de timp. 
S� se planifice proiectele (f�r� a se suprapune ca timp) astfel �nc�t s� se 
maximizeze profitul total. 

Fisierul �proiecte.txt� contine, pe fiecare linie, numele, termenul limit� 
si profitul asociat unui proiect. 

�n fisierul �profit.txt� s� se afiseze succesiunea de proiecte alese si 
profitul total obtinut prin realizarea lor.

Indicatie de rezolvare:
-	Se sorteaz� lista de proiecte descresc�tor dup� profit.
-	Folosind un dictionar care contine un num�r de intr�ri egal cu maximul 
termenelor limit�, se va �ncerca planificarea fiec�rui proiect c�t mai 
aproape de termenul s�u limit�.

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
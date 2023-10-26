""" 11. Definiții
Un student vrea, pentru ora de engleză de la FMI, să găsească cele mai expresive
cuvinte. Pentru aceasta a făcut o poză la astfel de cuvinte dintr-un dicționar,
iar apoi a folosit un program ca să extragă un șir de caractere cu textul din poze.
Textul respecta regulile:
• este împărțit în paragrafe, fiecare paragraf terminându-se cu "\n";
• fiecare paragraf corespunde unei intrări din dicționar, respectiv conține un
cuvânt și definițiile sale;
• cuvântul asociat unui paragraf se află la începutul său, fiind urmat de ":"
și apoi de toate definițiile sale.

Acum, studentul vrea sa decidă care sunt cele mai expresive cuvinte.
În acest scop, el numără pentru fiecare cuvânt în câte expresii apare
(Ex: run away, run over, run a company), astfel:
• numără de câte ori apare cuvântul în paragraf;
• numără de câte ori apare caracterul tilda (~) în paragraf;
• însumează cele două numere obținute.

Scrieți un program care să citească dintr-un fișier text șirul de caractere
extras și contruiește o listă de tupluri formate dintr-un cuvânt aflat la început
de paragraf și numărul care reprezintă expresivitatea sa calculată în acel paragraf."""

f = open("L3_pb11_definitii.txt", "r")
definitii = f.readlines()
f.close()

L = []
for linie in definitii:
    #print(linie, end="\n")
    [cuv, sir] = linie.split(":",1)
    cuvinte = [c.strip(" .,:;!?+-=") for c in sir.split()]
    nr1 = cuvinte.count(cuv)
    nr2 = sir.count("~") #; print(nr1, nr2)
    L.append((cuv,nr1+nr2))
print(L)
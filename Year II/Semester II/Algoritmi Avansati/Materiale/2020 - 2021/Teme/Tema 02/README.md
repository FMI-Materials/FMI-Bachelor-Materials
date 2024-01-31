# Tema Algoritmi genetici

Implementaţi un algoritm genetic pentru determinarea maximului unei funcţii pozitive pe un domeniu
dat (funcţia se va fixa în cod)
## Date de intrare:

- dimensiunea populaţiei
- domeniul de definiţie al funcţiei
- parametri pentru functia de maximizat (coeficientii polinomului de grad 2)
- precizia cu care se lucrează (cu care se discretizează intervalul)
- probabilitatea de recombinare (crossover, încrucişare)
- probabilitatea de mutaţie
- numărul de etape ale algoritmului
## Ieşire:
- Un fişier text sugestiv care evidenţiază operaţiile ​ **din prima etapă** ​ a algoritmului, (de
exemplu fişierului ​Evolutie.txt​ (obţinut pentru funcţia –x​^2 ​+x+2, domeniul [-1, 2],
dimensiunea populaţiei 20, precizia 6, probabilitatea de recombinare 0.25, probabilitatea de
mutaţie 0.01 şi 50 de etape))
- Bonus: Interfaţă grafică sugestivă, care evidenţiază evoluţia algoritmului

## În fişier sunt scrise
 - populaţia iniţială sub forma
i: reprezentare cromozom x = valoarea corespunzătoare cromozomului în domeniul de definiţie
al funcţiei f =valoarea corespunzătoare cromozomului (f(X​i​))
  - probabilităţile de selecţie pentru fiecare cromozom
  - probabilităţile cumulate care dau intervalele pentru selecţie
  - evidenţierea procesul de selecţie, care constă în generarea unui număr aleator u uniform pe
[0,1) şi determinarea intervalului [q​i​, q​i+1​) căruia aparține acest număr; corespunzător acestui
interval se va selecta cromozomul i+1. Procesul se repetă până se selectează numărul dorit de
cromozomi. ​ **Cerinţă:** căutarea intervalului corespunzător lui u se va face folosind căutarea
binară.
  - evidenţierea cromozomilor care participă la recombinare
  - pentru recombinările care au loc se evidenţiază perechile care participă la recombinare,
punctul de rupere generat aleator precum şi cromozomii rezultaţi în urma recombinării (sau,
după caz, se evidenţiază tipul de încrucişare ales)
  - populaţia rezultată după recombinare
  - populaţia rezultată după mutaţii
  - pentru restul generaţiilor (populaţiilor din etapele următoare) se vor afişa doar valoarea
maximă ​si valoarea medie a performantei.


**Se vor folosi metoda de codificare discutată la curs si încrucisarea cu un punct de tăietură
(rupere). Se va tine cont si de slectia de tip elitist (individul cu indicele de fitness cel mai mare va
trece automat in generatia urmatoare).**



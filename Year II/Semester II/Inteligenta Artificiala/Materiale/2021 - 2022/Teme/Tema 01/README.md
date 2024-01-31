## Evadarea lui Mormocel

Descriere completă: http://irinaciocan.ro/inteligenta_artificiala/exemple-teme-a-star.php

O broscuta mica de tot statea pe o frunza la fel de mica, ce plutea alene pe suprafata unui lac. Broscuta, spre deosebire de alte surate de-ale sale nu stia sa inoate si nu-i placea apa si poate de aceea isi dorea tare mult sa scape din lac si sa ajunga la mal. Singurul mod in care putea sa realizeze acest lucru era sa sara din frunza in frunza.

Forma lacului poate fi aproximata la un cerc. Coordonatele frunzelor sunt raportate la centrul acestui cerc (deci originea axelor de coordonate, adica punctul (0,0) se afla in centrul cercului). Lungimea unei sarituri e maxim valoarea greutatii/3. Din cauza efortului depus, broscuta pierde o unitate de energie(greutate) la fiecare saritura. Se considera ca pierderea in greutate se face in timpul saltului, deci cand ajunge la destinatie are deja cu o unitate mai putin. Daca broscuta ajunge la greutatea 0, atunci moare.

Pe unele frunze exista insecte, pe altele nu. Cand broscuta ajunge pe o frunza mananca o parte din insectele gasite si acest lucru ii da energie pentru noi sarituri. In fisierul de intrare se va specifica numarul de insecte gasite pe fiecare frunza. Daca broscuta mananca o insecta, ea creste in greutate cu o unitate. Atentie, odata ce a mancat o parte din insectele de pe o frunza, aceasta ramane bineinteles fara acel numar de insecte. O tranzitie e considerata a fi un salt plus consumarea insectelor de pe frunza pe care a ajuns.

Format fișier:
```
raza
GreutateInitialaBroscuta
id_frunza_start
identificator_frunza_1 x1 y1 nr_insecte_1 greutate_max_1
...
identificator_frunza_n xn yn nr_insecte_n greutate_max_n
```

Exemplu:
```
7
5
id1
id1 0 0 0 5
id2 -1 1 3 8
id3 0 2 0 7
id4 2 2 3 10
id5 3 0 1 5
id6 -3 1 1 6
id7 -4 1 3 7
id8 -4 0 1 7
id9 -5 0 2 8
id10 -3 -3 4 10
```

Exemplu de drum:
```
1)Broscuta se afla pe frunza initiala id1(0,0).
Greutate broscuta: 5
2)Broscuta sarit de la id1(0,0) la id2(-1,1).
Broscuta a mancat 2 insecte. Greutate broscuta: 6
3)Broscuta sarit de la id2(-1,1) la id6(-3,1).
Broscuta a mancat 1 insecte. Greutate broscuta: 6
4)Broscuta sarit de la id6(-3,1) la id8(-4,0).
Broscuta a mancat 1 insecte. Greutate broscuta: 6
5)Broscuta sarit de la id8(-4,0) la id9(-5,0).
Broscuta a mancat 1 insecte. Greutate broscuta: 6
6)Broscuta a ajuns la mal in 5 sarituri.
```

## Barem

Barem (punctajul e dat in procentaje din punctajul maxim al temei; procentajul maxim este 100%):
 - [x] (5%)Fișierele de input vor fi într-un folder a cărui cale va fi dată
    în linia de comanda. În linia de comandă se va da și calea pentru un
    folder de output în care programul va crea pentru fiecare fișier de
    input, fișierul sau fișierele cu rezultatele. Tot în linia de
    comandă se va da ca parametru și numărul de soluții de calculat (de
    exemplu, vrem primele NSOL=4 soluții returnate de fiecare algoritm).
    Ultimul parametru va fi timpul de timeout. Se va descrie în
    documentație forma în care se apelează programul, plus 1-2 exemple
    de apel.
 - [x] (5%) Citirea din fisier + memorarea starii. Parsarea fișierului de
    input care respectă formatul cerut în enunț
 - [x] (15%) Functia de generare a succesorilor
 - [x] (5%) Calcularea costului pentru o mutare
 - [x] (10%) Testarea ajungerii în starea scop (indicat ar fi printr-o
    funcție de testare a scopului)
 - [x] (15% = 2+5+5+3 ) 4 euristici:
    - [x] (2%) banala
    - [x] (5%+5%) doua euristici admisibile posibile (se va justifica la
        prezentare si in documentație de ce sunt admisibile)
    - [x] (3%) o euristică neadmisibilă (se va da un exemplu prin care se
        demonstrează că nu e admisibilă). Atenție, euristica
        neadmisibilă trebuie să depindă de stare (să se calculeze în
        funcție de valori care descriu starea pentru care e calculată
        euristica).

 - [x] (10%) crearea a 4 fisiere de input cu urmatoarele proprietati:
    - [x]  un fisier de input care nu are solutii
    - [x]  un fisier de input care da o stare initiala care este si finala
        (daca acest lucru nu e realizabil pentru problema, aleasa, veti
        mentiona acest lucru, explicand si motivul).
    - [x]  un fisier de input care nu blochează pe niciun algoritm și să
        aibă ca soluții drumuri lungime micuță (ca să fie ușor de
        urmărit), să zicem de lungime maxim 20.
    - [x]  un fisier de input care să blocheze un algoritm la timeout, dar
        minim un alt algoritm să dea soluție (de exemplu se blochează
        DF-ul dacă soluțiile sunt cât mai "în dreapta" în arborele de
        parcurgere)
    - [x]  dintre ultimele doua fisiere, cel putin un fisier sa dea drumul
        de cost minim pentru euristicile admisibile si un drum care nu e
        de cost minim pentru cea euristica neadmisibila

 - [x] (15%) Pentru cele NSOL drumuri(soluții) returnate de fiecare
    algoritm (unde NSOL e numarul de soluții dat în linia de comandă) se
    va afișa:

    - [x] lungimea drumului
    - [x] costului drumului
    - [x] timpul de găsire a unei soluții (**atenție**, pentru soluțiile de la a doua încolo timpul se consideră tot de la începutul execuției algoritmului și nu de la ultima soluție)
    - [x] numărul maxim de noduri existente la un moment dat în memorie
    - [x] numărul total de noduri calculate (totalul de succesori generati; atenție la DFI și IDA\* se adună pentru fiecare iteratie chiar dacă se repetă generarea arborelui, nodurile se vor contoriza de fiecare dată afișându-se totalul pe toate iterațiile

    Obținerea soluțiilor se va face cu ajutorul fiecăruia dintre
    algoritmii studiați:

    -   **Pentru studenții de la seria CTI problema se va rula cu
        algoritmii: BF, DF, DFI, UCS, Greedy, A\*.**
    -   **Pentru studenții din seriile Mate-Info și Informatică,
        problema se va rula cu algoritmii: UCS, A\* (varianta care dă
        toate drumurile), A\* optimizat (cu listele open și closed, care
        dă doar drumul de cost minim), IDA\*.**

    Pentru toate variantele de A* (cel care oferă toate drumurile, cel
    optimizat pentru o singură soluție, și IDA*) se va rezolva problema
    cu fiecare dintre euristici. Fiecare din algoritmi va fi rulat cu
    timeout, si se va opri daca depășește acel timeout (necesar în
    special pentru fișierul fără soluții unde ajunge să facă tot
    arborele, sau pentru DF în cazul soluțiilor aflate foarte în dreapta
    în arborele de parcurgere).

 - [x] (5%) Afisarea in fisierele de output in formatul cerut
 - [x] (5%) Validări și optimizari. Veți implementa elementele de mai jos
    care se potrivesc cu varianta de temă alocată vouă:
    - [x] găsirea unui mod de reprezentare a stării, cât mai eficient
    - [x] verificarea corectitudinii datelor de intrare
    - [x] găsirea unor conditii din care sa reiasă că o stare nu are cum
        sa contina in subarborele de succesori o stare finala deci nu
        mai merita expandata (nu are cum să se ajungă prin starea
        respectivă la o stare scop)
    - [x] găsirea unui mod de a realiza din starea initială că problema nu
        are soluții. Validările și optimizările se vor descrie pe scurt
        în documentație.

 - [x] (5%) Comentarii pentru clasele și funcțiile adăugate de voi în
    program (dacă folosiți scheletul de cod dat la laborator, nu e
    nevoie sa comentați și clasele existente). Comentariile pentru
    funcții trebuie să respecte un stil consacrat prin care se
    precizează tipul și rolurile parametrilor, căt și valoarea returnată
    (de exemplu, [reStructured
    text](https://www.python.org/dev/peps/pep-0287/) sau *[Google python
    docstrings](https://sphinxcontrib-napoleon.readthedocs.io/en/latest/example_google.html)*).
 - [x] (5%) Documentație cuprinzând explicarea euristicilor folosite. În
    cazul euristicilor admisibile, se va dovedi că sunt admisibile. În
    cazul euristicii neadmisibile, se va găsi un exemplu de stare
    dintr-un drum dat, pentru care h-ul estimat este mai mare decât h-ul
    real. Se va crea un tabel în documentație cuprinzând informațiile
    afișate pentru fiecare algoritm (lungimea și costul drumului,
    numărul maxim de noduri existente la un moment dat în memorie,
    numărul total de noduri). Pentru variantele de A* vor fi mai multe
    coloane în tabelul din documentație: câte o coloană pentru fiecare
    euristică. Tabelul va conține datele pentru minim 2 fișiere de
    input, printre care și fișierul de input care dă drum diferit pentru
    euristica neadmisibilă. În caz că nu se găsește cu euristica
    neadmisibilă un prim drum care să nu fie de cost minim, se acceptă
    și cazul în care cu euristica neadmisibilă se obțin drumurile în
    altă ordine decât crescătoare după cost, adică diferența să se vadă
    abia la drumul cu numărul K, K\>1). Se va realiza sub tabel o
    comparație între algoritmi și soluțiile returnate, pe baza datelor
    din tabel, precizând și care algoritm e mai eficient în funcție de
    situație. Se vor indica pe baza tabelului ce dezavantaje are fiecare
    algoritm.

        
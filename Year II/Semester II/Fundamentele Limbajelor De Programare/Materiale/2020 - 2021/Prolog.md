# :owl: SWI-Prolog :owl:

####    :globe_with_meridians: Link-uri utile
[Ninety-Nine Prolog Problems](https://www.ic.unicamp.br/~meidanis/courses/mc336/problemas-prolog/)

[Arithmetic and lists in Prolog](https://faculty.nps.edu/ncrowe/book/chap5.html)

[Modele de examen Prolog](https://drive.google.com/drive/folders/1c2Li1PU1xak6993LknH6oQkThiCiLNK9?fbclid=IwAR3ouvZHxrnJtRuCzbSM1-yWcgQ9YAxM3XLQFghMv8NObWT5siTYIMxtk3A)

## :pushpin: [Solutii si rezolvari](#cuprins) 

## Laboratoare Prolog

* [Lab 1](https://github.com/DimaOanaTeodora/Prolog-Classes/blob/main/Prolog1.pdf)
* [Lab 2](https://github.com/DimaOanaTeodora/Prolog-Classes/blob/main/Prolog2.pdf)
* [Lab 3](https://github.com/DimaOanaTeodora/Prolog-Classes/blob/main/Prolog3.pdf)
* [Lab 4](https://github.com/DimaOanaTeodora/Prolog-Classes/blob/main/Prolog4.pdf)

# :world_map: Teorie folositoare 

### Generalitati si terminologie

- Variabilele incep cu litera MARE sau cu _ +litera mica
- Atomii sunt cu litera MICA sau intre ' '
- La finalul fiecarui rand (instructiune) se pune .
- Citeste mereu instructiunile de sus in jos
- Incarcare fisier ['C:/Users/Lenovo/Desktop/Prolog/kb1.pl']. sau doar [nume_fisier].
- Constantele sunt atomi/numere
- Termenii compusi (PREDICATE) sunt formati dintr-un atom si mai multi termeni: nume_atom(t1, t2,..)

  :warning: NU se pune spatiu intre numele atomului si paranteza :warning:
  
- Aritatea este numarul de termeni si se noteaza: nume_atom/nr_termeni
- Regula(afirmatia) este de forma HEAD :- BODY
- Faptul este o regula fara body

  :warning: Faptele si regulile se grupeaza mereu dupa numele atomilor :warning:
 
- La recursivitate conditia de oprire trebuie sa fie mereu prima
  
### Ce returneaza?

Prolog pune intrebari si intoarce raspunsuri de tipul true/false. Daca predicatele din intrebare au variabile => da valorile posibile pentru care predicatele sunt true.

### Operatori diversi

- , inseamna SI
- ; inseamna SAU
- :- inseamna IMPLICATIE (un fel de "daca")
- \+ este negatia unui predicat (imi da si variabilele instantiate)
- not doar imi neaga raspunsul, dar nu-mi da variabilele instantiate
- fail/0 predicat care esueaza mereu
- ! este un predicat predefinit care opreste mecanismul de backtracking

### Comentarii

% pe o singura linie 

/* pe mai multe linii */

### Operatori

- Operatorul = compara termenii(expresiile), nu valorile si cauta un unificator
```
   ?- 3+5 = 5+3.
      false
   ?- 3+5 = 8. 
      false
   ?- 2 ** 3 = 3 + 5.
      false
 ```
- Compararea aritmetica: is/2, =:=/2, =\=/2 >/2, </2, >=/2, <=/2
- Impartirea reala: /
- Impartirea intreaga: //
- Restul impartirii: operatorul mod
- Inmultire: * 
- Ridicare la putere: ** 
```
   ?- 3+5 is 8.
      true
   ?- X is 3+5.
      X = 8
   ?- X = 1, 4 is 3+X.
      X = 1
   ?- 8 > 3.
      true
   ?- 8 =\= 3.
      true
 ```
- Functii predefinite: 
  - min/2
  - abs/2
  - sqrt/1
  - sin/1 etc.

### Liste

- Listele sunt ca in Haskell - pot sa combin cate tipuri vreau
- [HEAD | TAIL]
  - TAIL : LISTA cu coada
  - HEAD : valoare/variabila

### Functii pentru prelucrarea listelor

- Un predicat care verifica daca o lista contine un anumit termen:
 ```
    element_of(X,[X | _]).
    element_of(X,[_ | T]) :- element_of(X,T).
 ```
- Un predicat care concateneaza doua liste:
 ```
  concat_lists([], L, L).
  concat_lists([X | L1], L2, [X | L3]) :- concat_lists(L1, L2, L3).
 ```
- Predicatele predefinite:
  - length(lista, lungime_lista)
  - member(element de cautat, lista in care cauta)
  - append(l1, l2, l3=l1+l2),
  - last(lista, argument) => true daca argument este ultimul in lista
  - reverse(lista, lista oglindita)
  - write/1 (afiseaza un string primit intre '')
  - nl/0 (trece la randul urmator la afisare)
  ```
  ?- write('Hello World!'), nl.
     Hello World!
     true
  ```
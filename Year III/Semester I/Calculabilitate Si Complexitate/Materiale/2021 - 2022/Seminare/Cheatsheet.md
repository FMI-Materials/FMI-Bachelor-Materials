# Cheat Sheet

## Inmultire

### O Banda

 `[ a | b ] => [a | b | a*b]`

Avem `a` `1`-uri urmate de `b` `1`-uri. Vrem sa adaugam `a*b` `1`-uri la sfarsitul benzii.

 * Ciclam:
    * Daca nu mai este niciun `1` in `a`, atunci iesim din ciclu.
    * Marcam primul `1` din `a` in `2`.
    * Ciclam:
        * Daca nu mai este niciun `1` in `b`, atunci iesim din cilu.
        * Marcam primul `1` din `b` in `2`.
        * Adaugam un `1` la sfarsitul benzii.
    * Marcam toti `2` din `b` inapoi in `1`.
* Marcam toti `2` din `a` inapoi in `1`.

Complexitate: O(a * (a + b * (b + a * b))) = O(a^2 * b^2)

### Mai Multe Benzi

`B1[a], B2[b], B3[] => B1[a], B2[b], B3[a*b]`

* Ciclam:
    * Daca pe B1 am dat de Blank, atunci iesim din ciclu.
    * Ne mutam la dreapta pe B1.
    * Ciclam:
        * Daca pe B2 am dat de Blank, atunci iesim din ciclu.
        * Ne ducem in dreapta pe B2.
        * Adaugam un 1 si ne ducem la dreapta pe B3.
    * Punem cursorul de pe B2 inapoi la inceputul benzii.
* Mutam cursorul de pe B1 si B3 inapoi la inceputul benzii.

Complexitatea: O(a * b)

## Impartire

### O Banda

`[a | b] => [a | b | a/b]`

* Ciclam:
    * Ciclam:
        * Daca `b` nu mai contine niciun `1`, atunci iesim din ciclu.
        * Marcam primul `1` din `b` in `2`.
        * Daca `a` nu contine niciun `1`, atunci iesim din AMBELE cicluri.
        * Marcam primul `1` din `a` in `2`.
    * Adaugam `1` la sfarsitul benzii.
    * Marcam toti `2` din `b` in `1`.
* Marcam inapoi toti `2` din `a` si `b` in `1`.

Complexitate: O(max(a^2, a*b))

### Mai Multe Benzi

`B1[a], B2[b], B3[] => B1[a], B2[b], B3[a/b]`

* Ciclam:
    * Daca dam de Blank pe banda B2, atunci
        * Adaugam un `1` la sfarsitul benzii B3.
        * Mutam acul de citire la inceputul benzii B2.
    * Daca dam de un Blank pe banda B1, atunci iesim din ciclu.

Complexitate: O(a)

## Radical

### O Banda

`[a] => [a | b=sqrt(a)]`

* Adaugam un `0` dupa `a` pe banda (setam `b=0`).
* Ciclam:
    * Pentru fiecare element din `b`:
        * Daca nu sunt doua elemente nemarcate in `a`, atunci iesim din cicluri.
        * Marcam doua elemente din `a`.
    * Daca nu mai exista niciun element nemarcat in `a`, atunci iesim din ciclu.
    * Marcam un element in `a`.
    * Crestem `b` cu `1`.

Complexitate: O(a^2)

### Mai Multe Benzi

Ne folosim de faptul ca 1+3+5+...+ 2k+1 = k^2

`B1[a], B2[] => B1[a], B2[sqrt(a)]`

* Ciclam:
    * Pentru fiecare element din banda B2:                   -- scadem 2*x din a
        * Mergem doua pozitii la dreapta pe banda B1.
        * Daca am citit un Blank, iesim din AMBELE cicluri.
    * Mergem la dreapta pe banda B1.                        -- scadem 1 din a
    * Daca am citit un Blank pe B1, atunci iesim din ciclu.
    * Adaugam un `1` in banda B2.

Complexitate: O(a).

## Log

### O Banda

`[a] => [a | Lg_k(a)]`

* Ciclam:
    * Ne punem acul de citire la inceputul benzii.
    * Ne ducem in dreapta, pana iesim din a, facand:
        * Daca dam de un `2`, trecem mai departe.
        * Marcam cate `K-1` `1`-uri in `2`, si lasam al `K`-lea `1` neschimbat.
    * Daca am dat de cel putin un `1` in parcurgerea de mai sus, atunci adaugam un `1` la sfarsitul benzii.
    * Daca nu, iesim din ciclu.

Complexitate: O(lg(a) * a)

### Mai Multe Benzi

`B1[a], B2[], B3[] => B1[???], B2[???], B3[Lg+k(a)]`

* Ciclam:
    * Mutam acul de citire la inceputul benzii B1.
    * Golim si multam acul de citire la inceputul benzii B2.
    * Ne ducem in dreapta pe banda B1, facand:
        * Daca dam de un `2`, trecem mai departe.
        * Marcam cate `K` `1`-uri in `2`, si la fiecare al `K`-lea `1`, adaugam un `1` pe banda B2.
    * Daca banda B2 este goala, atunci iesim din ciclu.
    * Adaugam un `1` in banda B3.
    * Stergem tot ce este pe banda B1.
    * Copiem ce este pe banda B2 pe banda B1.

Complexitate: O(a)


## Test Primalitate

### O Banda

`[N] => [N | sqrt(N)] => [2222111111111]`

* Marcam manual pe prima pozitie ca fiind `0` (1 nu e prim).
* Ciclam:
    * Gasim primul 1. Daca nu exista niciun `1`, am terminat si iesim din ciclu.
    * Marcam `1` si tot ce e in stanga lui cu `&`.
    * Ciclam cat timp exista elemente ne-marcate nici cu `&` nici cu `$`:
        * Pentru fiecare element marcat cu `&`:
            * Gasim primul element care sa nu fie marcat nici cu `&` nici cu `$`, si il marcam cu `$`.
            * Daca acum suntem la ultimul element marcat cu `&`, atunci schimbam valoarea in `0`.
    * Scoatem toate markele (`&` si `$`).
    * Schimbam primul `1` in `2` (specificam ca am procesat acel numar prim).
* Daca ultima pozitie este `1` sau `2`, atunci numarul initial este prim, daca este `0`, atunci este neprim.

Complexitate: O(N^3 / log(N))

Optional, putem sa:
* Calculam `sqrt(N)`, si marcam primele `sqrt(N)` pozitii din ciur.
* Nu propagam numerele prime in multiplii decat daca fac parte din primele `sqrt(N)` numere marcate mai sus.

Noua complexitate este: O(N^2.5 / log(N))

### Mai Multe Benzi

`B1[N], B2[], B3[] => B1[N], B2[sqrt(N)], B3[???]` 

* Calculam pe banda B2 `sqrt(N)` in O(N)
* Marcam primele `sqrt(N)` elemente din B1 (parcurgand in paralel B1 si B2).
* Marcam primul `1` din B1 in `0` (1 nu e prim).
* Cat timp exista un `1` pe B1, care sa fie marcat (`<= sqrt(N)`):
    * Punem capul de citire al lui B1 pe primul `1`, si al lui B3 la inceputul benzii.
    * Punem pe B3 atatea `1` cate pozitii avem in stanga (avansam in paralel in stanga pe B1 si dreapta pe B3).
    * Ne punem capetele de citire al lui B1 si B3 la inceputul benzii.
    * Cat timp nu am dat de Blank pe B1, ne ducem cu ambele in paralel la dreapta:
        * Daca dam de un Blank pe B3, atunci:
            * Setam elementul curent de pe B1 `0`.
            * Mutam capatul de citire de pe B3 la inceputul benzii.
    * Schimbam primul `1` din B1 in `2`.
* Daca ultima pozitie este `1` sau `2`, atunci numarul initial este prim, daca este `0`, atunci este neprim.

Complexitate: O(N^1.5 / log(N))



## Recunoscut Limbajul { A AT A }




 * Complexitatea pe masina nedeterminista: nr min sau maxim de pasi?
 * Accepare pe nedeterminist: O ramura se opreste si accepta?
 * Calculare pe nedeterminist: Cum??
 
 
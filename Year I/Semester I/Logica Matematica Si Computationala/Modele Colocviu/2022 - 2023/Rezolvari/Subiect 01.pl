/*
Problema 1
Teste:
1) ?- consec([5, 4, 3, 2, 1]).
2) ?- consec([1, 2, 3, 5, 4]).
3) ?- consec([3, 4, 5, 6, 7]).

Rezultate:
1) false
2) false
3) true

Explicatie:
consec([]) si consec[[X]] sunt implicit adevarate.
consec([X, Y|T]) verifica daca elementele X si Y sunt consecutive cu intructiunea Y =:= X + 1, care evalueaza mai intai X + 1 si apoi il compara cu Y.
Daca intructiunea este adevarata, se trece recursiv in lista fara X, si anume prin consec([Y|T]).
 */
consec([]).
consec([_]).
consec([X, Y|T]):- 
    Y =:= X + 1, consec([Y|T]).

/*
Problema 2
Teste:
1) ?- lista_angajati([angajat(ion, 10), angajat(mirela, 11), angajat(marcel, 12), angajat(ioana, 13), angajat(andrei, 14)], 12, R).
2) ?- lista_angajati([angajat(mircea, 100), angajat(ioana, 200), angajat(mihai, 300)], 301, R).
3) ?- lista_angajati([angajat(a, 9), angajat(b, 8), angajat(c, 7), angajat(d, 6), angajat(e, 5), angajat(f, 4), angajat(g, 3)], 2, R).

Rezultate:
1) R = [ioana, andrei]
2) R = []
3) R = [a, b, c, d, e, f, g]

Explicatie:
lista_angajati([], _, []) reprezinta cazul de baza, care returneaza o lista vida cand lista de angajati este vida, oricat ar fi pragul de salariu
lista_angajati([angajat(X, Y)|T], S, [X|R]) reprezinta cazul in care Y, adica salariul angajatului X, este strict mai mare decat pragul de salariu, caz in care X se adauga la R prin [X|R] si se apleaza recursiv lista_angajati(T, S, R).
lista_angajati([angajat(_, Y)|T], S, R) reprezinta cazul in care Y este mai mic sau egal fata de pragul de salariu, caz in care nu se adauga nimic la R si se apleaza recursiv pana la lista vida.
 */
lista_angajati([], _, []).
lista_angajati([angajat(X, Y)|T], S, [X|R]):-
    Y > S, lista_angajati(T, S, R).
lista_angajati([angajat(_, Y)|T], S, R):-
    Y =< S, lista_angajati(T, S, R).
:- ensure_loaded("02").
:- ensure_loaded("03").

eval(X, E, A):-
    atom(X), val(X, E, A).
eval(non(X), E, A):-
    eval(X, E, B), bnon(B, A).
eval(si(X, Y), E, A):-
    eval(X, E, B), eval(Y, E, C), bsi(B, C, A).
eval(sau(X, Y), E, A):-
    eval(X, E, B), eval(Y, E, C), bsau(B, C, A).
eval(imp(X, Y), E, A):-
    eval(X, E, B), eval(Y, E, C), bimp(B, C, A).
plus(0, X, X).
plus(s(Y), X, s(Z)) :- plus(Y, X, Z).

:- a(a, a(1)) == a(a, a(1)).
:- a(a, a(1)) == _X.

:- a(a, a(1)) = X, write(X).
:- a(a, a(1)) = a(X), write(X).  % failing
:- a(a, a(1)) = a(X, Y), write(X), nl, write(Y).  % works

eq(A, B) :-   % =:=
    X is A,
    Y is B,
    X == Y.

intexp(I) :- integer(I).
intexp(A) :- var(A), !, fail.
intexp(A + B) :- intexp(A), intexp(B).

cauta(X, X) :- integer(X).
cauta(X + A, Y) :- intexp(A), X1 is Y - A, cauta(X, X1).
cauta(A + X, Y) :- intexp(A), X1 is Y - A, cauta(X, X1).

%merge(L1,L2, L)

merge([],L2, L2).
merge(L1, [], L1).
merge([H1|T1], [H2|T2], [H|T]) :-
    H1 < H2
    ->  H = H1, merge(T1, [H2|T2], T)
    ;   H = H2, merge([H1|T1], T2, T).



map(_, [], []).
map(F, [H|T], [H1| T1]) :- map(F, T, T1), call(F, H, H1).

in_tree(E, n(_, E, _)).
in_tree(E, n(Left, _, Right)) :- in_tree(E, Left) ; in_tree(E, Right).
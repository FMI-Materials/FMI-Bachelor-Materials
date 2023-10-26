parent(bob, lisa).
parent(bob, paul).
parent(bob, mary).
parent(juliet, lisa).
parent(juliet, paul).
parent(juliet, mary).
parent(peter, harry).
parent(lisa, harry).
parent(mary, dony).
parent(mary, sandra).

ancestor_of(X, Y) :-
    parent(X, Y).

ancestor_of(X, Y) :-
    parent(X, Z), ancestor_of(Z, Y).
vars(V, [V]):- 
    atom(V).
vars(non(X), S):-
    vars(X, S).
vars(si(X, Y), S):-
    vars(X, T), vars(Y, U), union(T, U, S).
vars(sau(X, Y), S):-
    vars(X, T), vars(Y, U), union(T, U, S).
vars(imp(X, Y), S):-
    vars(X, T), vars(Y, U), union(T, U, S).
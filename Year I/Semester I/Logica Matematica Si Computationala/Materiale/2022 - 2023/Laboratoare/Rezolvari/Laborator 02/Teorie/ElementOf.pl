element_of(X, [X|_]).
element_of(X, [_|Tail]):-
    element_of(X, Tail).
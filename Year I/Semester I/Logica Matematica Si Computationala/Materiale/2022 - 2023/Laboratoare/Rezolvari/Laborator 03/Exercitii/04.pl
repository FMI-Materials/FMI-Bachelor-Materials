insert(X, [], [X]).
insert(X, [H|T], [X|[H|T]]):-
    X < H.
insert(X, [H|T], [H|L]):-
    X >= H, insert(X, T, L).

insertsort([],[]).
insertsort([H|T], L):- 
    insertsort(T, L1), insert(H, L1, L).
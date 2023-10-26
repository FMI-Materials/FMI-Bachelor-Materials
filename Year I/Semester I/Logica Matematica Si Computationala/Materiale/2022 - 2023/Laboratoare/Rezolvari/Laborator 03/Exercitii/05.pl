split(_, [], [], []).
split(X, [H|T], [H|A], B):-
    H < X, split(X, T, A, B).
split(X, [H|T], A, [H|B]):-
    H >= X, split(X, T, A, B).

quicksort([],[]).
quicksort([H|T], L) :-
    split(H, T, A, B), quicksort(A, M), quicksort(B, N), append(M, [H|N], L).


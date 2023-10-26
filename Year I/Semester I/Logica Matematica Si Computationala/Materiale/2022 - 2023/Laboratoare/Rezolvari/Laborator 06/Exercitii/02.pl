split(_, [], [], []).
split(X, [H|T], [H|A], B):-
    H < X, split(X, T, A, B).
split(X, [H|T], A, [H|B]):-
    H >= X, split(X, T, A, B).
quicksort([], []).
quicksort([H|T], L) :-
    split(H, T, A, B), quicksort(A, M), quicksort(B, N), append(M, [H|N], L).

quicksortdh([], (R, R)).
quicksortdh([H|T], (R, S)):- 
    split(H, T, A, B), quicksortdh(A, (R, [H|N])), quicksortdh(B, (N, S)).
quicksortd(L, R):- 
    quicksortdh(L,(R,[])).
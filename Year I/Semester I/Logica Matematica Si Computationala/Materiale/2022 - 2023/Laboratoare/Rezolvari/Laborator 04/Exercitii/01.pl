listaNelem(_, 0, []).
listaNelem(L, N, [H|T]):-
    N > 0, P is N - 1, member(H, L), listaNelem(L, P, T).
listaNelem(L, N, LL):-
    bagof(M, listaNelem(L, N, M), LL).

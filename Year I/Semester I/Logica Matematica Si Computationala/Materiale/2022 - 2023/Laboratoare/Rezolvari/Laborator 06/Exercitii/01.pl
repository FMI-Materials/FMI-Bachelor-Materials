flatten([], []).
flatten([H|T], L):-
    flatten(H, P), flatten(T, Q), append(P, Q, L).
flatten(X, [X]):-
    \+ is_list(X).

flattendh([], (R, R)).
flattendh([H|T], (R, S)):-
    flattendh(H, (R, N)), flattendh(T, (N, S)).
flattendh([H|T], ([H|R], S)):-
    \+ is_list(H), flattendh(T, (R, S)).
flattend(L, R):-
    flattendh(L, (R, [])).
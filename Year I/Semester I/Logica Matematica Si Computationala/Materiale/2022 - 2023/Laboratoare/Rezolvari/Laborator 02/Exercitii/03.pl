line(0, _):-
line(N, C):-
    1 =< N, write(C), M is N - 1, line(M, C).
square_aux(_, 0, _):-
    nl.
square_aux(N, M, C):-
    1 =< M, line(N, C), nl, M1 is M - 1, square_aux(N, M1, C).
square(N, C):-
    square_aux(N, N, C).
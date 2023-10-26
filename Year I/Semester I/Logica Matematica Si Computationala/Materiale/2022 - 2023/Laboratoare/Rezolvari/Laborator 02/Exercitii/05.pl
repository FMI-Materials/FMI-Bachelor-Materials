scalarMult(_, [], []).
scalarMult(N, [H1|T1], [H2|T2]):-
    H2 is N * H1, scalarMult(N, T1, T2).

dot([], [], 0).
dot([H1|T1], [H2|T2], Result):-
    dot(T1, T2, Temp), Result is H1 * H2 + Temp.

max([], 0).
max([H|T], Y):-
    max(T, Y), Y >= H.
max([H|T], H):-
    max(T, Y), H > Y.
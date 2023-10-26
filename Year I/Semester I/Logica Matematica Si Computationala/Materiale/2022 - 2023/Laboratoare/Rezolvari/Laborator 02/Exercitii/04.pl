all_a([]).
all_a([a|T]):-
    all_a(T).

trans_a_b([], []).
trans_a_b([a|T1], [b|T2]):-
    trans_a_b(T1, T2).
remove_duplicates([], []).
remove_duplicates([H|T], [H|T1]):-
    \+ member(H, T), remove_duplicates(T, T1).
remove_duplicates([H|T], T1):-
    member(H, T), remove_duplicates(T, T1).

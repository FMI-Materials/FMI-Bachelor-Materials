rev([], []).
rev([H|T], L):-
    rev(T, Z), append(Z, [H], L).

palindrome(L):-
    rev(L, L).

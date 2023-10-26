% 01) my_last([a, b, c, d], X).
my_last([X], X).
my_last([_|T], X):-
    my_last(T, X).

% 02) almost_last([a, b, c, d], X).
almost_last([X, _], X).
almost_last([_|T], X):-
    almost_last(T, X).

% 03) element_at([a, b, c, d, e], 3, X).
element_at([X|_], 1, X).
element_at([_|T], N, X):-
    element_at(T, M, X), N is M + 1.

% 04) el_count([1, 2, 3, 4, 5], X).
el_count([], 0).
el_count([_|T], N):-
    el_count(T, M), N is M + 1.

% 05) reverse([5, 4, 3, 2, 1], L).
reverse([], []).
reverse([H|T], L):-
    reverse(T, Temp), append(Temp, [H], L).

% 06) palindrome([x,a,m,a,x]).
palindrome(L):-
    reverse(L, L).

% 07) my_flatter([a, [b, [c, d], e]], X).
my_flatter([], []).
my_flatter([H|T], L):-
    my_flatter(H, L1), my_flatter(T, L2), append(L1, L2, L).
my_flatter(X, [X]):-
    \+ is_list(X).

% 08) compress([a, a, a, a, b, c, c, a, a, d, e, e, e, e], X).
compress([X], [X]).
compress([X, Y|T], [X|L]):-
    X \= Y, compress([Y|T], L).
compress([X, X|T], L):-
    compress([X|T], L).

% 09) pack([a, a, a, a, b, c, c, a, a, d, e, e, e, e], X).
take(X, [X|T], U, V) :- take(X, T, P, V), append([X], P, U).
take(_, L, [], L).
pack([], []).
pack([X|T], Z):-
    take(X, T, P, Q), pack(Q, V), append([X], P, R), append([R], V, Z).

% 10) encode([a, a, a, a, b, c, c, a, a, d, e, e, e, e], X).
encode([], []).
encode([X|T], Z):-
    take(X, [X|T], P, Q), length(P, Len), encode(Q, V), append([[Len, X]], V, Z).

% 11) encode_modified([a, a, a, a, b, c, c, a, a, d, e, e, e, e], X).
encode_modified([], []).
encode_modified([X|T], Z):-
    take(X, [X|T], P, Q), length(P, Len), Len > 1, encode_modified(Q, V), append([[Len, X]], V, Z).
encode_modified([X|T], Z):-
    take(X, [X|T], P, Q), length(P, Len), Len == 1, encode_modified(Q, V), append([X], V, Z).

% 12) decode([[4, a], b, [2, c], [2, a], d, [4, e]], X).
cpy(1, X, [X]).
cpy(N, X, [X|V]):-
    1 < N, M is N - 1, cpy(M, X, V).
decode([], []).
decode([[N, X]|T], L):-
    cpy(N, X, P), decode(T, Q), append(P, Q, L).
decode([H|T], L):-
    cpy(1, H, P), decode(T, Q), append(P, Q, L).

% 13) encode_direct([a, a, a, a, b, c, c, a, a, d, e, e, e, e], X).
count(X, [], [], 1, X).
count(X, [], [], N, [N, X]):-
    N > 1.
count(X, [Y|Ys], [Y|Ys], 1, X):-
    X \= Y.
count(X, [Y|Ys], [Y|Ys], N, [N, X]):-
    N > 1, X \= Y.
count(X, [X|Xs], Ys, K, T):-
    K1 is K + 1, count(X, Xs, Ys, K1, T).
encode_direct([], []).
encode_direct([X|Xs], [Z|Zs]):-
    count(X, Xs, Ys, 1, Z), encode_direct(Ys, Zs).

% 14) dupli([a, b, c, c, d], X).
dupli([], []).
dupli([H|T], [H, H|V]):-
    dupli(T, V).

% 15) dupli([a, b, c], 3, X).
dupli([], _, []).
dupli([H|T], N, L):-
    cpy(N, H, P), dupli(T, N, Q), append(P, Q, L). 


% 16) drop([a, b, c, d, e, f, g, h, i, k], 3, X).
drop_aux([], _, _, []).
drop_aux([H|T], K, N, [H|L]):-
    K \= N, K1 is K + 1, drop_aux(T, K1, N, L).
drop_aux([_|T], K, N, L):-
    K == N, K1 is 1, drop_aux(T, K1, N, L).
drop(L, N, X):-
    drop_aux(L, 1, N, X). 

% 17) split([a, b, c, d, e, f, g, h, i, k], 3, L1, L2).
split([H|T], N, [H|L1], L2):-
    M is N - 1, split(T, M, L1, L2).
split(L, 0, [], L).

% 18) slice([a, b, c, d, e, f, g, h, i, k], 3, 7, L).
slice_aux([], _, _, _, []).
slice_aux([H|T], K, Left, Right, [H|L]):-
    K >= Left, K =< Right, K1 is K + 1, slice_aux(T, K1, Left, Right, L).
slice_aux([_|T], K, Left, Right, L):-
    (K < Left; K > Right), K1 is K + 1, slice_aux(T, K1, Left, Right, L).
slice(L, Left, Right, X):-
    slice_aux(L, 1, Left, Right, X).

% 19) rotate([a, b, c, d, e, f, g, h], -2, X).
rotate([], _, []).
rotate(L, N, X):-
    N >= 0, split(L, N, L1, L2), append(L2, L1, X).
rotate(L, N, X):-
    N < 0, length(L, Len), M is Len + N, split(L, M, L1, L2), append(L2, L1, X).

% 20) remove_at([a, b, c, d], 2, X, R).
remove_at_aux([], _, _, _, []).
remove_at_aux([H|T], K, N, H, R):-
    K == N, K1 is K + 1, remove_at_aux(T, K1, N, _, R).
remove_at_aux([H|T], K, N, X, [H|R]):-
    K \= N, K1 is K + 1, remove_at_aux(T, K1, N, X, R).
remove_at(L, N, X, R):-
    remove_at_aux(L, 1, N, X, R).

% 21) insert_at(alfa, [a, b, c, d], 2, L).
insert_at_aux(_,[], _, _, []).
insert_at_aux(Word, [H|T], K, N, [H|L]):-
    K \= N, K1 is K + 1, insert_at_aux(Word, T, K1, N, L).
insert_at_aux(Word, [H|T], K, N, [Word, H|L]):-
    K == N, K1 is K + 1, insert_at_aux(Word, T, K1, N, L).
insert_at(Word, L, N, X):-
    insert_at_aux(Word, L, 1, N, X).

% 22) range(4, 9, L).
range_aux(K, _, Right, []):-
    K > Right.
range_aux(K, Left, Right, [K|L]):-
    K >= Left, K =< Right, K1 is K + 1, range_aux(K1, Left, Right, L).
range(Left, Right, L):-
    range_aux(Left, Left, Right, L).

% 23) rnd_select([a, b, c, d, e, f, g, h], 3, L).
rnd_select(_, 0, []).
rnd_select(Xs, N, [X|Zs]):-
    N > 0, length(Xs, L), I is random(L) + 1, remove_at(Xs, I, X, Ys), N1 is N - 1, rnd_select(Ys, N1, Zs).

% 24) lotto(6, 49, L).
lotto(0, _, []).
lotto(N, Right, L):-
    range(1, Right, R), rnd_select(R, N, L).

% 25) rnd_permu([a, b, c, d, e, f], L).
rnd_permu(L, X):-
    length(L, N), rnd_select(L, N, X).

% 26) combination(3, [a, b, c, d, e, f], L).
el([X|L], X, L).
el([_|L], X, R):-
    el(L, X, R).
combination(0, _, []).
combination(K, L, [X|Xs]):-
    K > 0, el(L, X, R), K1 is K - 1, combination(K1, R, Xs).
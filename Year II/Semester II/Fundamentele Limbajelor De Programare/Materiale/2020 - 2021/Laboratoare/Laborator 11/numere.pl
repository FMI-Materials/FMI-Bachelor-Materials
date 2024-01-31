is_cifra(X) :- between(0, 9, X).
is_cifra1(X) :- between(1, 9, X).

% 1935 se reprezinta ca [5,3,9,1] 

is_numar1([H]) :- is_cifra1(H), !.
is_numar1([H|T]) :- is_cifra(H), is_numar1(T).

is_numar([0]).
is_numar(L) :- is_numar1(L).

nat_to_numar(0, [0]) :- !.
nat_to_numar(N, L) :- nat_to_numar1(N, L).

nat_to_numar1(0, []).
nat_to_numar1(N, [C | R1]) :-
  N > 0,
  divmod(N, 10, N1, C),
  nat_to_numar1(N1, R1)
  .

numar_to_nat([], 0).
numar_to_nat([H|T], N) :-
  numar_to_nat(T, N1),
  N is N1 * 10 + H.

% zece(0,0,0, 0, 0).
% zece(0,1,0, 0, 1).
% zece(0,2,0, 0, 2).
% zece(0,3,0, 0, 3).
% zece(0,4,0, 0, 4).
% zece(0,5,0, 0, 5).
% zece(0,6,0, 0, 6).

sum(N1, N2, N) :- sum1(0, N1, N2, N).
sum1(0, [], [], []) :- !.
sum1(C, [], N2, N) :- sum1(C, [0], N2, N).
sum1(C, N1, [], N) :- sum1(C, N1, [0], N).
sum1(C, [H1|T1], [H2|T2], [H|T]) :-
   % zece(H1, H2, C, C1, H),
   S is H1 + H2 + C,
   divmod(S, 10, C1, H),
   sum1(C1, T1, T2, T).


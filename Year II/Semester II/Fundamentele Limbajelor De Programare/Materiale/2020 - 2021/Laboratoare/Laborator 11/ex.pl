/* 1 */
distance((X, Y), (XX, YY), D) :- L is (X - XX) ** 2,
                                 R is (Y - YY) ** 2,
                                 D is sqrt(L + R).
/* 2 */
fib(0, X) :- X is 0.
fib(1, X) :- X is 1.
fib(N, X) :- N >= 2,
             N1 is N-1,
             N2 is N-2,
             fib(N1, L),
             fib(N2, R),
             X is L + R.

fib2(0, _, X, X).
fib2(N, A, B, Y) :- N>0,
                        Last is A + B,
                        NN is N-1,
                        fib2(NN, B, Last, Y).

fib3(K, A) :- fib2(K, 0, 1, A).

/* 3 */
line(0, _).
line(N, C) :- N > 0,
              write(C),
              N1 is N-1,
              line(N1, C).

square1(0, _).
square1(N, M, C) :- N > 0,
                line(M, C),
                write('\n'),
                N1 is N-1,
                square1(N1, M, C).

square(N, C) :- square1(N, N, C).

/* 4 */
all_a([]).
all_a([a|T]) :- all_a(T).
all_a(['A'|T]) :- all_a(T).

trans_a_b([], []).
trans_a_b([a|T1], [b|T2]) :- trans_a_b(T1, T2).

/* 5 */
scalarMult(_, [], []).
scalarMult(M, [H | T], [HH | TT]) :- MH is M * H,
                                     HH = MH,
                                     scalarMult(M, T, TT).

mul([], [], []).
mul([H | T], [HH | TT], [HHH | TTT]) :- HHH is HH * H,
                                        mul(T, TT, TTT).
sum([X], X).
sum([H|T], S) :- sum(T, X), S is H + X.
dot(L1, L2, R) :- mul(L1, L2, RR),
                  sum(RR, R).

max([X], X).
max([H | T], X) :- max(T, Y), 
                   X = ((H > Y) -> H; Y).

/* 6 */
palindrome(L) :- reverse(L, LL),
                 L == LL.


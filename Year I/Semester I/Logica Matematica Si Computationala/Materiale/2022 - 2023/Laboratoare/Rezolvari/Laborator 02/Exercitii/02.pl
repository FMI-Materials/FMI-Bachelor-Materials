fib1(0, 1).
fib1(1, 1).
fib1(N, X):-
    2 =< N, M is N - 1, fib1(M, Y), P is N - 2, fib1(P, Z), X is Y + Z.

fibo(0, 0, 1).
fibo(1, 1, 1).
fibo(N, Z, X):-
    2 =< N, M is N - 1, fibo(M, Y, Z), X is Y + Z.

fib2(N, X):- fibo1(N, _, X).
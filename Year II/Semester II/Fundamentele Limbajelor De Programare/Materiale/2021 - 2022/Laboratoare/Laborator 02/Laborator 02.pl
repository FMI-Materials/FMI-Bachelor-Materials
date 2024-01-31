distance((A,B),(C,D), X) :- X is sqrt((C-A)**2 + (D-B)**2).

fib(0,1).
fib(1,1).
fib(N, X) :- A is N - 1, B is N - 2, fib(A, X1), fib(B, X2), X is X1 + X2.

fibo(0,1).
fibo(1,1).
fibo(N, X) :- fibo(1, 1, 1, N, X).
fibo(_, F, N, N, F).
fibo(F0, F1, I, N, X) :- F2 is F0 + F1,
    J is I + 1, fibo(F1, F2, J, N, X).
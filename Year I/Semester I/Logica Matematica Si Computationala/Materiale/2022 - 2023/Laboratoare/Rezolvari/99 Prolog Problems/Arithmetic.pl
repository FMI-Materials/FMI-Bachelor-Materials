% 1) is_prime(7).
has_factor(N, L):- 
    N mod L =:= 0.
has_factor(N, L):- 
    L * L < N, L2 is L + 2, has_factor(N, L2).
is_prime(2).
is_prime(3).
is_prime(P):- 
    integer(P), P > 3, P mod 2 =\= 0, \+ has_factor(P, 3). 

% 2) prime_factors(315, L).
next_factor(_,2,3):- !.
next_factor(N,F,NF):- 
    F * F < N, !, NF is F + 2.
next_factor(N, _, N). 
prime_factors(N, L):- 
    N > 0,  prime_factors(N, L, 2).
prime_factors(1, [], _):- !.
prime_factors(N,[F|L],F):-
    R is N // F, N =:= R * F, !, prime_factors(R, L, F).
prime_factors(N, L, F) :- 
   next_factor(N, F, NF), prime_factors(N, L, NF).

% 3) prime_factors_mult(315, L).
divi(N, F, M, R, K):- 
    S is N // F, N =:= S * F, !, K1 is K + 1, divi(S, F, M, R, K1).
divi(N, _, M, N, M).
divide(N, F, M, R) :- divi(N, F, M, R, 0), M > 0.
prime_factors_mult(N, L):- 
    N > 0, prime_factors_mult(N, L, 2).
prime_factors_mult(1, [], _):- !.
prime_factors_mult(N, [[F, M]|L], F):- 
    divide(N, F, M, R), !, next_factor(R, F, NF), prime_factors_mult(R, L, NF).
prime_factors_mult(N, L, F):- 
    !, next_factor(N, F, NF), prime_factors_mult(N, L, NF).

% 4) prime_list(1, 100, L).
next(2, 3):- !.
next(A, A1):- 
    A1 is A + 2.
p_list(A, B, []):- 
    A > B, !.
p_list(A, B, [A|L]):- 
    is_prime(A), !, next(A, A1), p_list(A1, B, L). 
p_list(A, B, L):- 
   next(A, A1), p_list(A1, B, L).
prime_list(A, B, L):- 
    A =< 2, !, p_list(2, B, L).
prime_list(A, B, L):- 
    A1 is (A // 2) * 2 + 1, p_list(A1, B, L).

% 5) goldbach(28, L).
next_prime(P, P1):- 
    P1 is P + 2, is_prime(P1), !.
next_prime(P, P1):- 
    P2 is P + 2, next_prime(P2, P1).
goldbach(4,[2, 2]):- !.
goldbach(N, L):- 
    N mod 2 =:= 0, N > 4, goldbach(N, L, 3).
goldbach(N, [P, Q], P):- 
    Q is N - P, is_prime(Q), !.
goldbach(N, L, P):- 
    P < N, next_prime(P, P1), goldbach(N, L, P1).

% 6) goldbach_list(9,20).
print_goldbach(A, P, Q, L):- 
    P >= L, !, writef('%t = %t + %t', [A, P, Q]), nl.
print_goldbach(_, _, _, _).
g_list(A, B, _):- 
    A > B, !.
g_list(A, B, L):- 
   goldbach(A, [P, Q]), print_goldbach(A, P, Q, L), A2 is A + 2, g_list(A2, B, L).
goldbach_list(A, B):- 
    goldbach_list(A, B, 2).
goldbach_list(A, B, L):- 
    A =< 4, !, g_list(4, B, L).
goldbach_list(A, B, L):- 
    A1 is ((A + 1) // 2) * 2, g_list(A1, B, L).

% 7) G is gcd(36, 63).
gcd(X, 0, X):- 
    X > 0.
gcd(X,Y,G):- 
    Y > 0, Z is X mod Y, gcd(Y, Z, G).
:- arithmetic_function(gcd/2).

% 8) coprime(35, 64).
coprime(X, Y) :- gcd(X, Y, 1).

% 9) Phi is totient_phi(10).
t_phi(M, Phi, M, Phi):- !.
t_phi(M, Phi, K, C):- 
   K < M, coprime(K, M), !, C1 is C + 1, K1 is K + 1, t_phi(M, Phi, K1, C1).
t_phi(M, Phi, K, C):- 
   K < M, K1 is K + 1, t_phi(M, Phi, K1, C).
totient_phi(1, 1):- !.
totient_phi(M, Phi):- 
    t_phi(M, Phi, 1, 0).
:- arithmetic_function(totient_phi/1).

% 10) totient_phi(10, X).
to_phi([], 1).
to_phi([[F, 1]|L], Phi):- 
    !, to_phi(L, Phi1), Phi is Phi1 * (F - 1).
to_phi([[F, M]|L], Phi):- 
    M > 1, M1 is M - 1, to_phi([[F, M1]|L], Phi1), Phi is Phi1 * F.
totient_phi_2(N, Phi):- 
    prime_factors_mult(N, L), to_phi(L, Phi).

% 11)
totient_test(N):-
   write('totient_phi (p2_09):'), time(totient_phi(N, Phi1)), write('result = '), write(Phi1), nl,
   write('totient_phi_2 (p2_10):'), time(totient_phi_2(N, Phi2)), write('result = '), write(Phi2), nl.